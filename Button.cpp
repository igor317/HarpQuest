#include "Button.h"

/**
 * Конструктор Button
 * Инициализирует кнопку и настраивает пин как вход
 * 
 * @param pin номер пина, к которому подключена кнопка
 */
Button::Button(int pin)
{
    // Сохраняем номер пина
    m_Pin = pin;
    
    // Настраиваем пин как вход
    pinMode(m_Pin, INPUT);
    
    // Инициализируем таймеры
    m_Timer = millis();
    m_Delta = m_Timer;
}

/**
 * Деструктор Button
 * Освобождает ресурсы, занятые кнопкой и функциями обратного вызова
 */
Button::~Button()
{
    // Освобождаем память, занятую функциями обратного вызова
    for (int i = 0; i < m_TimeoutCallback.Size(); ++i)
        delete m_TimeoutCallback[i];
    
    // Очищаем вектор функций обратного вызова
    m_TimeoutCallback.Clear();
}

/**
 * Основной метод обработки кнопки
 * Должен вызываться в цикле loop()
 * Обрабатывает нажатия и вызывает соответствующие функции
 */
void Button::Run()
{
    // Проверяем, нажата ли кнопка (сигнал на пине соответствует уровню срабатывания)
    if (digitalRead(m_Pin) == m_TriggeredLevel)
    {
        // Вычисляем, сколько времени кнопка находится в нажатом состоянии
        m_Delta = millis() - m_Timer;

        // Если время нажатия больше задержки для устранения дребезга,
        // считаем кнопку нажатой
        if (m_Delta > BUTTON_BOUNCE_DELAY)
        {
            m_Pressed = true;
        }
    }
    else // Кнопка не нажата
    {
        // Сбрасываем таймер нажатия
        m_Timer = millis();
        
        // Если кнопка была нажата, а теперь отпущена, обрабатываем событие
        if (m_Pressed)
        {
            // Если есть зарегистрированные функции обратного вызова
            if (m_TimeoutCallback.Size())
            {
                // Ищем подходящую функцию обратного вызова на основе времени удержания
                TimeoutCallback* timeoutCallback = nullptr;
                unsigned long currentTimeout = 0;
                
                for (int i = 0; i < m_TimeoutCallback.Size(); ++i)
                {
                    // Выбираем функцию с максимальным таймаутом, но не превышающим время удержания кнопки
                    if (m_TimeoutCallback[i]->timeout >= currentTimeout &&
                        m_TimeoutCallback[i]->timeout <= m_Delta)
                    {
                        currentTimeout = m_TimeoutCallback[i]->timeout;
                        timeoutCallback = m_TimeoutCallback[i]; 
                    }
                }
                
                // Если подходящая функция найдена, вызываем все функции из этой группы
                if (timeoutCallback)
                {
                    for (int i = 0; i < timeoutCallback->function.Size(); ++i)
                        timeoutCallback->function[i]->exec();
                }
            }

            // Сбрасываем флаг нажатия
            m_Pressed = false;
        }
    }
}

/**
 * Устанавливает уровень сигнала, при котором кнопка считается нажатой
 * 
 * @param level уровень срабатывания (true - HIGH, false - LOW)
 */
void Button::SetTriggeredLevel(bool level)
{
    m_TriggeredLevel = level;
}

/**
 * Добавляет функцию обратного вызова, которая будет вызвана при нажатии кнопки
 * 
 * @param callback указатель на функцию, которая будет вызвана
 * @param timeout время в миллисекундах, после которого будет вызвана функция
 *                (0 - вызов при обычном нажатии, >0 - вызов при удержании)
 */
void Button::AddClickCallback(EventFunc* callback, unsigned long timeout)
{
    // Ищем группу функций с таким же таймаутом
    for (int i = 0; i < m_TimeoutCallback.Size(); ++i)
    {
        if (m_TimeoutCallback[i]->timeout == timeout)
        {
            // Если группа найдена, добавляем функцию в эту группу
            m_TimeoutCallback[i]->function.Add(callback);
            return;
        }
    }

    // Если группа с таким таймаутом не найдена, создаем новую группу
    TimeoutCallback* timeoutCallback = new TimeoutCallback();
    timeoutCallback->function.Add(callback);
    timeoutCallback->timeout = timeout;

    // Добавляем новую группу в список
    m_TimeoutCallback.Add(timeoutCallback);
}