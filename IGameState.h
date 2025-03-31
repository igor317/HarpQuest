/**
 * IGameState.h - Базовый интерфейс для всех состояний игры
 * 
 * Этот класс является базовым для всех состояний игры и определяет
 * интерфейс, который должны реализовать все конкретные состояния.
 * 
 * Игра HarpQuest использует паттерн проектирования "Состояние" (State Pattern),
 * который позволяет объекту изменять своё поведение в зависимости от 
 * внутреннего состояния.
 * 
 * В игре используются следующие состояния:
 * - NormalGameState - обычный режим игры
 * - CalibrationState - режим калибровки
 * - FinishGameState - состояние завершения игры
 */

#ifndef IGAMESTATE_H
#define IGAMESTATE_H

#include "config.h"
#include "GameManager.h"
class GameManager;

class IGameState
{
protected:
    // Указатель на менеджер игры
    // Каждое состояние имеет доступ к менеджеру для управления игрой
    GameManager* m_GameManager;
public:
    /**
     * Конструктор IGameState
     * 
     * @param manager указатель на менеджер игры
     */
    IGameState(GameManager* manager);
    
    /**
     * Виртуальный деструктор
     * Необходим для правильного удаления объектов производных классов
     */
    virtual ~IGameState();

    void SetState(IGameState* state);

    /**
     * Основной метод, который должен быть реализован всеми состояниями
     * Вызывается в цикле игры и определяет поведение игры в данном состоянии
     */
    virtual void Run() = 0;
};

#endif