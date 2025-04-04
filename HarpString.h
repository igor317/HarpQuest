/**
 * HarpString.h - Класс для работы со "струной" арфы
 * 
 * Этот класс представляет одну "струну" арфы, которая на самом деле
 * является фоторезистором, подключенным к аналоговому входу Arduino.
 * Класс позволяет проверить, "задета" ли струна в данный момент.
 */

#ifndef HARPSTRING_H
#define HARPSTRING_H

#include "Arduino.h"
#include "config.h"

class HarpString
{
private:
    // Номер аналогового пина, к которому подключен фоторезистор
    int m_Pin;
public:
    /**
     * Конструктор HarpString
     * 
     * @param pin номер аналогового пина, к которому подключен фоторезистор
     */
    HarpString(int pin);
    
    /**
     * Получает текущее значение с аналогового пина (0-1023)
     * 
     * @return текущее значение с фоторезистора (0-1023)
     */
    int GetValue();
    
    /**
     * Проверяет, "задета" ли струна в данный момент
     * В зависимости от настройки HARPSTRING_HIGHLIGHTED_DEFAULT,
     * струна считается задетой при повышении или понижении значения
     * 
     * @return true если струна задета, false если нет
     */
    bool IsTriggered();
};

#endif