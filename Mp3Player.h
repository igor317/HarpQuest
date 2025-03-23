//#include "DFPlayer_Mini_Mp3.h>

#ifndef MP3PLAYER_H
#define MP3PLAYER_H

#include "config.h"
#include "DFPlayer_Mini_Mp3.h"

class Mp3Player
{
private:
    static int m_BusyPin;
public:
    static void Init(HardwareSerial& hserial, int busyPin);
    static void SetVolume(uint8_t volume);
    static bool PlaySample(uint16_t sampleId, bool force = false);
    static void WaitUntilFinish();
};

#endif
