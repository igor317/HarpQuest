#include "Button.h"

Button::Button(int pin)
{
    m_Pin = pin;
    pinMode(m_Pin, INPUT);
    m_Timer = millis();
    m_Delta = m_Timer;
}

Button::~Button()
{
    for (int i = 0;i<m_TimeoutCallback.Size();++i)
        delete m_TimeoutCallback[i];
    m_TimeoutCallback.Clear();
}

void Button::Run()
{
    if (digitalRead(m_Pin) == m_TriggeredLevel)
    {
        m_Delta = millis() - m_Timer;

        if (m_Delta > BUTTON_BOUNCE_DELAY)
        {
            m_Pressed = true;
 
        }
    }
    else
    {
        m_Timer = millis();
        if (m_Pressed)
        {
            if (m_TimeoutCallback.Size())
            {
                TimeoutCallback* timeoutCallback = nullptr;
                unsigned long currentTimeout = 0;
                for (int i = 0;i<m_TimeoutCallback.Size();++i)
                {
                    if (m_TimeoutCallback[i]->timeout >= currentTimeout &&
                        m_TimeoutCallback[i]->timeout <= m_Delta)
                        {
                            currentTimeout = m_TimeoutCallback[i]->timeout;
                            timeoutCallback = m_TimeoutCallback[i]; 
                        }
                }
                if (timeoutCallback)
                {
                    for (int i = 0;i<timeoutCallback->function.Size();++i)
                        timeoutCallback->function[i]->exec();
                }

            }

            m_Pressed = false;
        }

    }
}

void Button::SetTriggeredLevel(bool level)
{
    m_TriggeredLevel = level;
}

void Button::AddClickCallback(EventFunc* callback, unsigned long timeout)
{
    for (int i = 0;i<m_TimeoutCallback.Size();++i)
    {
        if (m_TimeoutCallback[i]->timeout == timeout)
        {
            m_TimeoutCallback[i]->function.Add(callback);
            return;
        }
    }

    TimeoutCallback* timeoutCallback = new TimeoutCallback();
    timeoutCallback->function.Add(callback);
    timeoutCallback->timeout = timeout;

    m_TimeoutCallback.Add(timeoutCallback);
}