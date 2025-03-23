#ifndef FINISHGAMESTATE_H
#define FINISHGAMESTATE_H

#include "IGameState.h"

class FinishGameState : public IGameState
{
public:
    FinishGameState(GameManager* manager);

    void Run();
};

#endif