#include "CalibrationState.h"

CalibrationState::CalibrationState(GameManager* manager) : IGameState(manager)
{
#ifdef DEBUG_LOG
    Serial.println();
    Serial.println("Set calibration mode");
    Serial.println();
#endif
    Mp3Player::PlaySample(SAMPLE_START_CALIBRATION);
    Mp3Player::WaitUntilFinish();

    m_GameManager->GetGameSequence()->Clear();
}

bool CalibrationState::SaveSequenceToEEPROM(int address)
{
#ifdef DEBUG_LOG
    Serial.println();
    Serial.println("Start saving sequence to EEPROM");
    Serial.print("Code address: ");
    Serial.println(address);
#endif

    Sequence* gameSequence = m_GameManager->GetGameSequence();

    int numElements = gameSequence->Length();

    if (!numElements)
    {
#ifdef DEBUG_LOG
        Serial.println("ERROR: code sequence is empty");
        Serial.println();
#endif
        return false;
    }

    EEPROM[address] = numElements;
    for (int i = 0;i<gameSequence->Length();++i)
        EEPROM[address + i + 1] = gameSequence->GetValue(i);

#ifdef DEBUG_LOG
    Serial.print("Loaded Data ");
    for (int i = 0;i<gameSequence->Length();++i)
        Serial.print(gameSequence->GetValue(i));
    Serial.println();
#endif
    return true;
}

void CalibrationState::Run()
{
    Sequence* gameSequence = m_GameManager->GetGameSequence();
    HarpString* harpString = m_GameManager->GetHarpStringBuffer();
    int numHarpString = m_GameManager->GetNumHarpStrings();

    if (gameSequence->Length() && millis() - m_Timer > END_CALIBRATION_INTERVAL)
    {
#ifdef DEBUG_LOG
        Serial.println();
        Serial.println("Code is selected");
        for (int i = 0;i<gameSequence->Length();++i)
            Serial.print(gameSequence->GetValue(i));
        Serial.println();
#endif

        for (int j = 0;j<gameSequence->Length();++j)
        {
            Mp3Player::PlaySample(gameSequence->GetValue(j),true);
            Mp3Player::WaitUntilFinish();
        }

        Mp3Player::PlaySample(SAMPLE_END_CALIBRAION);
        Mp3Player::WaitUntilFinish();
        SaveSequenceToEEPROM(EEPROM_DATA_START_ADDRESS);

        m_GameManager->SetState(new NormalGameState(m_GameManager));
        return;
    }

    for (int i = 0;i<numHarpString;++i)
    {
        if (m_LastPressedHarp != i && harpString[i].IsTriggered())
        {
            m_LastPressedHarp = i;
#ifdef DEBUG_LOG
            Serial.println();
            Serial.print("Set data ");
            Serial.println(i);
#endif
            
            gameSequence->AddValue(i + 1);
            Mp3Player::PlaySample(i + 1,true);
            m_Timer = millis();
            break;
        }
    }
}