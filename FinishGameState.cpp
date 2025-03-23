#include "FinishGameState.h"
#include "NormalGameState.h"

FinishGameState::FinishGameState(GameManager* manager) : IGameState(manager)
{
#ifdef DEBUG_LOG
    Serial.println();
    Serial.println("Set finish mode");
    Serial.println();
#endif
}

void FinishGameState::Run()
{
#ifdef DEBUG_LOG
    Serial.println("Enable lock for ");
    Serial.print(FINISH_GAME_TIMEOUT);
    Serial.print(" ms");
#endif
    digitalWrite(LOCKER_PIN,HIGH);
    delay(FINISH_GAME_TIMEOUT);
    digitalWrite(LOCKER_PIN,LOW);

    SetState(new NormalGameState(m_GameManager));
}