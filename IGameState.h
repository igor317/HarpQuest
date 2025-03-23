#ifndef IGAMESTATE_H
#define IGAMESTATE_H

#include "config.h"
#include "GameManager.h"
class GameManager;

class IGameState
{
protected:
    GameManager* m_GameManager;
public:
    IGameState(GameManager* manager);
   // virtual ~IGameState() = 0;

    void SetState(IGameState* state);

    virtual void Run() = 0;
};

#endif