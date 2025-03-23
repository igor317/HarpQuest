#include "Mp3Player.h"

int Mp3Player::m_BusyPin;

void Mp3Player::Init(HardwareSerial& hserial, int busyPin)
{
    m_BusyPin = busyPin;

    pinMode(m_BusyPin, INPUT);

    hserial.begin(9600);
    mp3_set_serial(hserial);
}

void Mp3Player::SetVolume(uint8_t volume)
{  
    mp3_set_volume(volume); 
}

bool Mp3Player::PlaySample(uint16_t sampleId, bool force)
{
    if (digitalRead(m_BusyPin) || force)
    {
        mp3_play(sampleId);
        delay(200);
        return true;
    }
    return false;
}

void Mp3Player::WaitUntilFinish()
{
    while (!digitalRead(m_BusyPin)) {}
}