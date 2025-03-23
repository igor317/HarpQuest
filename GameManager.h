#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <EEPROM.h>

#include "Sequence.h"
#include "HarpString.h"
#include "Mp3Player.h"
#include "IGameState.h"

class IGameState;

class GameManager
{
private:
    Sequence m_PlayerSequence;
    Sequence m_GameSequence;
    HarpString* m_HarpString;
    int m_NumHarpString;

    IGameState* m_CurrentState = nullptr;

    bool finished = false;
    void(*m_SuccessfullCallback)() = nullptr;
    void(*m_ResetCallback)() = nullptr;
public:
    friend class IGameState;

    GameManager();

    void Init(HarpString* harpString, int numHarpString);

    void Reset();

    void EnterCalibrationMode();
    void ExitCalibrationMode();

    void SetSuccessfulCallback(void(*callback)());
    void SetResetCallback(void(*callback)());

    void SetState(IGameState* state);

    HarpString* GetHarpStringBuffer();
    int GetNumHarpStrings();

    Sequence* GetPlayerSequence();
    Sequence* GetGameSequence();

    bool LoadGameSequenceFromEEPROM(int address);

    void Run();
};

#endif