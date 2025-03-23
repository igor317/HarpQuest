#include "IGameState.h"

IGameState::IGameState(GameManager* manager)
{
    m_GameManager = manager;
}

void IGameState::SetState(IGameState* state)
{
    m_GameManager->SetState(state);
}