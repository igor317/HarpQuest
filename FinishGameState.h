/**
 * FinishGameState.h - Состояние завершения игры
 * 
 * Этот класс представляет состояние, в которое переходит игра
 * после успешного ввода правильной последовательности.
 * В этом состоянии открывается замок и воспроизводится
 * звуковой сигнал успешного завершения.
 */

#ifndef FINISHGAMESTATE_H
#define FINISHGAMESTATE_H

#include "IGameState.h"

class FinishGameState : public IGameState
{
public:
    /**
     * Конструктор FinishGameState
     * 
     * @param manager указатель на менеджер игры
     */
    FinishGameState(GameManager* manager);

    /**
     * Основной цикл состояния завершения игры
     * Открывает замок, воспроизводит звук и через заданное время
     * возвращает игру в нормальное состояние
     */
    void Run();
};

#endif