#ifndef NORMALGAMESTATE_H
#define NORMALGAMESTATE_H

#include "IGameState.h"
#include "FinishGameState.h"

class NormalGameState : public IGameState
{
private:
    bool m_Finished = false;
    
    int m_LastPressedHarp = -1;

    void Reset();
public:
    NormalGameState(GameManager* manager);
    ~NormalGameState();

    void Run();
};

#endif