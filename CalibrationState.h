#ifndef CALIBRATIONSTATE_H
#define CALIBRATIONSTATE_H

#include "IGameState.h"
#include "NormalGameState.h"
#include <EEPROM.h>

class CalibrationState : public IGameState
{
private:
    unsigned long m_Timer;
    int m_LastPressedHarp = -1;

    bool SaveSequenceToEEPROM(int address);
public:
    CalibrationState(GameManager* manager);

    void Run();
};

#endif