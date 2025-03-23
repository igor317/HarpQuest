#include "NormalGameState.h"

NormalGameState::NormalGameState(GameManager* manager) : IGameState(manager)
{
#ifdef DEBUG_LOG
    Serial.println();
    Serial.println("Set normal mode");
    Serial.print("Correct sequence: ");
    Sequence* gameSequence = m_GameManager->GetGameSequence();
    for (int i = 0;i<gameSequence->Length();++i)
        Serial.print(gameSequence->GetValue(i));
    Serial.println();
#endif

    Reset();
}

NormalGameState::~NormalGameState()
{

}

void NormalGameState::Reset()
{
    m_LastPressedHarp = -1;
    m_GameManager->GetPlayerSequence()->Clear();
}

void NormalGameState::Run()
{
    auto playerSequence = m_GameManager->GetPlayerSequence();
    auto gameSequence = m_GameManager->GetGameSequence();
    auto hartStringBuffer = m_GameManager->GetHarpStringBuffer();
    auto numHarpString = m_GameManager->GetNumHarpStrings();

    for (int i = 0;i<numHarpString;++i)
    {
        if (i != m_LastPressedHarp && hartStringBuffer[i].IsTriggered())
        {
            m_LastPressedHarp = i;
            playerSequence->AddValue(i + 1);
            Mp3Player::PlaySample(i + 1,true);
            if (playerSequence->Length() == gameSequence->Length())
            {
#ifdef DEBUG_LOG
                Serial.print("Selected sequence: ");
                for (int j = 0;j<playerSequence->Length();++j)
                {
                    Serial.print(playerSequence->GetValue(j));
                }
                Serial.println();
#endif
                Mp3Player::WaitUntilFinish();
                delay(WAIT_AFTER_END_SEQUENCE);
                
                for (int j = 0;j<playerSequence->Length();++j)
                {
                    Mp3Player::PlaySample(playerSequence->GetValue(j),true);
                    Mp3Player::WaitUntilFinish();
                }

                if (gameSequence->Compare(*playerSequence))
                {
#ifdef DEBUG_LOG
                    Serial.println("Sequence is correct");
#endif
                    m_GameManager->SetState(new FinishGameState(m_GameManager));
                    return;
                }
#ifdef DEBUG_LOG
                Serial.print("incorrect sequence");
                Serial.println();
#endif
                
                delay(1000);
                Reset();
            }
        }
    } 
}