#ifndef HARPSTRING_H
#define HARPSTRING_H

#include "Arduino.h"
#include "config.h"

class HarpString
{
private:
    int m_Pin;
public:
    HarpString(int pin);
    int GetValue();
    bool IsTriggered();
};

#endif