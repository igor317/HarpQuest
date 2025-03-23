#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "config.h"

class Sequence
{
private:
    int m_Buffer[MAX_SEQUENCE_LENGTH];
    int m_Length = 0;
public:
    Sequence();

    void AddValue(int value);

    int GetValue(int index);
    
    void Clear();
    int Length();

    bool Compare(Sequence& other);
};

#endif