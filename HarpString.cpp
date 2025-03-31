#include "HarpString.h"

/**
 * Конструктор HarpString
 * Инициализирует пин как вход
 * 
 * @param pin номер аналогового пина, к которому подключен фоторезистор
 */
HarpString::HarpString(int pin)
{
    // Сохраняем номер пина
    m_Pin = pin;
    
    // Настраиваем пин как вход
    pinMode(m_Pin, INPUT);
}

/**
 * Получает текущее значение с аналогового пина
 * 
 * @return текущее значение с фоторезистора (0-1023)
 */
int HarpString::GetValue()
{
    // Читаем аналоговое значение с пина (0-1023)
    return analogRead(m_Pin);
}

/**
 * Проверяет, "задета" ли струна в данный момент
 * 
 * Определяет, считается ли струна задетой, на основе значения и настройки:
 * - Если HARPSTRING_HIGHLIGHTED_DEFAULT определен: струна задета,
 *   когда значение БОЛЬШЕ порога (фоторезистор получает больше света)
 * - Если HARPSTRING_HIGHLIGHTED_DEFAULT не определен: струна задета,
 *   когда значение МЕНЬШЕ порога (фоторезистор получает меньше света)
 * 
 * @return true если струна задета, false если нет
 */
bool HarpString::IsTriggered()
{
#ifdef HARPSTRING_HIGHLIGHTED_DEFAULT
    // Струна задета, если значение БОЛЬШЕ порога
    return GetValue() > HARPSTIRNG_THRESHOLD;
#else
    // Струна задета, если значение МЕНЬШЕ порога
    return GetValue() < HARPSTIRNG_THRESHOLD;
#endif
}