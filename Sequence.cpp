#include "Sequence.h"


Sequence::Sequence()
{
    
}

void Sequence::AddValue(int value)
{
    m_Buffer[m_Length] = value;
    m_Length++;
}

int Sequence::GetValue(int index)
{
    if (index < 0 || index >= m_Length)
        return -1;

    return m_Buffer[index];
}

void Sequence::Clear()
{
    m_Length = 0;
}

int Sequence::Length()
{
    return m_Length;
}

bool Sequence::Compare(Sequence& other)
{   
    for (int i = 0;i<m_Length;++i)
        if (m_Buffer[i] != other.GetValue(i))
            return false;

    return true;
}
