#include "FinishGameState.h"
#include "NormalGameState.h"

/**
 * Конструктор FinishGameState
 * Инициализирует состояние завершения игры
 * 
 * @param manager указатель на менеджер игры
 */
FinishGameState::FinishGameState(GameManager* manager) : IGameState(manager)
{
#ifdef DEBUG_LOG
    // Выводим отладочную информацию о переходе в режим завершения
    Serial.println();
    Serial.println("Set finish mode");
    Serial.println();
#endif
}

/**
 * Основной цикл состояния завершения игры
 * Выполняется постоянно, пока это состояние активно
 */
void FinishGameState::Run()
{
#ifdef DEBUG_LOG
    // Выводим отладочную информацию о времени активации замка
    Serial.println("Enable lock for ");
    Serial.print(FINISH_GAME_TIMEOUT);
    Serial.print(" ms");
#endif
    
    // Активируем замок (HIGH - открыт, LOW - закрыт)
    digitalWrite(LOCKER_PIN, HIGH);
    
    // Ждем заданное время, в течение которого замок будет открыт
    delay(FINISH_GAME_TIMEOUT);
    
    // Закрываем замок
    digitalWrite(LOCKER_PIN, LOW);

    // Возвращаемся в нормальное состояние игры
    SetState(new NormalGameState(m_GameManager));
}