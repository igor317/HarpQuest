/**
 * GameManager.h - Менеджер игры
 * 
 * Этот класс является "сердцем" всей игры. Он управляет:
 * - последовательностями струн (игровой и введенной игроком)
 * - состояниями игры (нормальный режим, калибровка, завершение)
 * - "струнами" арфы
 * 
 * Менеджер предоставляет доступ к важным компонентам игры
 * и контролирует переходы между разными состояниями.
 */

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <EEPROM.h>

#include "Sequence.h"
#include "HarpString.h"
#include "Mp3Player.h"
#include "IGameState.h"

class IGameState;

class GameManager
{
private:
    // Последовательность нажатий, которую ввел игрок
    Sequence m_PlayerSequence;
    
    // Правильная последовательность нажатий для победы
    Sequence m_GameSequence;
    
    // Указатель на массив "струн" арфы
    HarpString* m_HarpString;
    
    // Количество "струн" в арфе
    int m_NumHarpString;

    // Текущее состояние игры (нормальное, калибровка, завершение)
    IGameState* m_CurrentState = nullptr;

    // Флаг завершения игры
    bool finished = false;
    
    // Функция обратного вызова, которая будет вызвана при успешном завершении игры
    void(*m_SuccessfullCallback)() = nullptr;
    
    // Функция обратного вызова, которая будет вызвана при сбросе игры
    void(*m_ResetCallback)() = nullptr;
public:
    // Разрешаем состояниям игры доступ к приватным полям менеджера
    friend class IGameState;

    /**
     * Конструктор GameManager
     * Создает новый менеджер игры с базовой последовательностью 1-2-3
     */
    GameManager();

    /**
     * Инициализация менеджера игры
     * 
     * @param harpString указатель на массив "струн" арфы
     * @param numHarpString количество "струн" в арфе
     */
    void Init(HarpString* harpString, int numHarpString);

    /**
     * Сбрасывает текущую игру в начальное состояние
     */
    void Reset();

    /**
     * Вход в режим калибровки
     */
    void EnterCalibrationMode();
    
    /**
     * Выход из режима калибровки
     */
    void ExitCalibrationMode();

    /**
     * Устанавливает функцию, которая будет вызвана при успешном завершении игры
     * 
     * @param callback функция, которая будет вызвана
     */
    void SetSuccessfulCallback(void(*callback)());
    
    /**
     * Устанавливает функцию, которая будет вызвана при сбросе игры
     * 
     * @param callback функция, которая будет вызвана
     */
    void SetResetCallback(void(*callback)());

    /**
     * Меняет текущее состояние игры на новое
     * 
     * @param state новое состояние игры
     */
    void SetState(IGameState* state);

    /**
     * Возвращает указатель на массив "струн" арфы
     * 
     * @return указатель на массив "струн"
     */
    HarpString* GetHarpStringBuffer();
    
    /**
     * Возвращает количество "струн" в арфе
     * 
     * @return количество "струн"
     */
    int GetNumHarpStrings();

    /**
     * Возвращает последовательность нажатий игрока
     * 
     * @return указатель на последовательность игрока
     */
    Sequence* GetPlayerSequence();
    
    /**
     * Возвращает правильную последовательность для победы
     * 
     * @return указатель на игровую последовательность
     */
    Sequence* GetGameSequence();

    /**
     * Загружает правильную последовательность из энергонезависимой памяти
     * 
     * @param address адрес в памяти, откуда загружать последовательность
     * @return true если загрузка прошла успешно, false если произошла ошибка
     */
    bool LoadGameSequenceFromEEPROM(int address);

    /**
     * Основной цикл менеджера игры
     * Вызывает метод Run текущего состояния игры
     */
    void Run();
};

#endif