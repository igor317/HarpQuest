#include "HarpString.h"

HarpString::HarpString(int pin)
{
    m_Pin = pin;
    pinMode(m_Pin,INPUT);
}

int HarpString::GetValue()
{
    return analogRead(m_Pin);
}

bool HarpString::IsTriggered()
{
#ifdef HARPSTRING_HIGHLIGHTED_DEFAULT
    return GetValue() > HARPSTIRNG_THRESHOLD;
#else
    return GetValue() < HARPSTIRNG_THRESHOLD;
#endif
}