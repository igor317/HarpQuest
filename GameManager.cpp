#include "GameManager.h"

GameManager::GameManager()
{
    m_GameSequence.AddValue(1);
    m_GameSequence.AddValue(2);
    m_GameSequence.AddValue(3);
}

void GameManager::Reset()
{
    if (m_ResetCallback)
        m_ResetCallback();
}

void GameManager::Init(HarpString* harpString, int numHarpString)
{
    m_HarpString = harpString;
    m_NumHarpString = numHarpString;

    //Reset();
}

void GameManager::SetSuccessfulCallback(void(*callback)())
{
    m_SuccessfullCallback = callback;
}

void GameManager::SetResetCallback(void(*callback)())
{
    m_ResetCallback = callback;
}

void GameManager::SetState(IGameState* state)
{
    if (m_CurrentState)
        delete m_CurrentState;

    m_CurrentState = state;
}

HarpString* GameManager::GetHarpStringBuffer()
{
    return m_HarpString;
}

int GameManager::GetNumHarpStrings()
{
    return m_NumHarpString;
}

Sequence* GameManager::GetPlayerSequence()
{
    return &m_PlayerSequence;
}

Sequence* GameManager::GetGameSequence()
{
    return &m_GameSequence;
}

bool GameManager::LoadGameSequenceFromEEPROM(int address)
{
#ifdef DEBUG_LOG
    Serial.println();
    Serial.println("Start reading sequence from EEPROM");
    Serial.print("Code address: ");
    Serial.println(address);
#endif

    int numElements = EEPROM[address];

    if (!numElements || numElements > MAX_SEQUENCE_LENGTH)
    {
#ifdef DEBUG_LOG
        Serial.println("ERROR: sequence is empty or more than MAX_SEQUENCE_LENGTH (");
        Serial.print(MAX_SEQUENCE_LENGTH);
        Serial.print(')');
        Serial.println();
#endif
        return false;
    }

    m_GameSequence.Clear();

    for (int i = 0;i<numElements;++i)
        m_GameSequence.AddValue(EEPROM[address + i + 1]);

#ifdef DEBUG_LOG
    Serial.print("Loaded Data ");
    for (int i = 0;i<m_GameSequence.Length();++i)
        Serial.print(m_GameSequence.GetValue(i));
    Serial.println();
#endif
    return true;
}

void GameManager::Run()
{
    if (m_CurrentState)
        m_CurrentState->Run();
}