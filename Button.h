#ifndef BUTTON_H
#define BUTTON_H

#include "Delegate.h"
#include "Vector.h"
#include "Arduino.h"

#define BUTTON_BOUNCE_DELAY 50

struct TimeoutCallback
{
	Vector<EventFunc*> function;
    unsigned long timeout;
};

class Button
{
public:
    int m_Pin;

    Vector<TimeoutCallback*> m_TimeoutCallback;
    unsigned long m_Timer;
    unsigned long m_Delta;
    bool m_Pressed = false;
    bool m_TriggeredLevel = true;
public:
    Button(int pin);
    ~Button();
    void Run();

    void SetTriggeredLevel(bool level);

    void AddClickCallback(EventFunc* callback, unsigned long timeout = 0);
};

#endif