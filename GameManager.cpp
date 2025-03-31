#include "GameManager.h"

/**
 * Конструктор GameManager
 * Создает новый менеджер игры и задает базовую последовательность 1-2-3
 */
GameManager::GameManager()
{
    // Устанавливаем начальную последовательность 1-2-3
    // Это будет использоваться если не удастся загрузить последовательность из EEPROM
    m_GameSequence.AddValue(1);
    m_GameSequence.AddValue(2);
    m_GameSequence.AddValue(3);
}

/**
 * Сбрасывает игру в начальное состояние
 * Если установлен callback для сброса, он будет вызван
 */
void GameManager::Reset()
{
    // Если установлен callback для сброса, вызываем его
    if (m_ResetCallback)
        m_ResetCallback();
}

/**
 * Инициализирует менеджер игры
 * 
 * @param harpString указатель на массив "струн" арфы
 * @param numHarpString количество "струн" в арфе
 */
void GameManager::Init(HarpString* harpString, int numHarpString)
{
    // Сохраняем указатель на "струны" и их количество
    m_HarpString = harpString;
    m_NumHarpString = numHarpString;

    // Раскомментируйте, если нужно сбрасывать игру при инициализации
    //Reset();
}

/**
 * Устанавливает функцию обратного вызова, которая будет вызвана при успешном завершении игры
 * 
 * @param callback функция, которая будет вызвана при успехе
 */
void GameManager::SetSuccessfulCallback(void(*callback)())
{
    m_SuccessfullCallback = callback;
}

/**
 * Устанавливает функцию обратного вызова, которая будет вызвана при сбросе игры
 * 
 * @param callback функция, которая будет вызвана при сбросе
 */
void GameManager::SetResetCallback(void(*callback)())
{
    m_ResetCallback = callback;
}

/**
 * Меняет текущее состояние игры на новое
 * Старое состояние будет удалено из памяти
 * 
 * @param state новое состояние игры
 */
void GameManager::SetState(IGameState* state)
{
    // Удаляем старое состояние из памяти, если оно есть
    if (m_CurrentState)
        delete m_CurrentState;

    // Устанавливаем новое состояние
    m_CurrentState = state;
}

/**
 * Возвращает указатель на массив "струн" арфы
 * 
 * @return указатель на массив "струн"
 */
HarpString* GameManager::GetHarpStringBuffer()
{
    return m_HarpString;
}

/**
 * Возвращает количество "струн" в арфе
 * 
 * @return количество "струн"
 */
int GameManager::GetNumHarpStrings()
{
    return m_NumHarpString;
}

/**
 * Возвращает последовательность нажатий игрока
 * 
 * @return указатель на последовательность игрока
 */
Sequence* GameManager::GetPlayerSequence()
{
    return &m_PlayerSequence;
}

/**
 * Возвращает правильную последовательность для победы
 * 
 * @return указатель на игровую последовательность
 */
Sequence* GameManager::GetGameSequence()
{
    return &m_GameSequence;
}

/**
 * Загружает правильную последовательность из энергонезависимой памяти (EEPROM)
 * 
 * @param address адрес в памяти, откуда загружать последовательность
 * @return true если загрузка прошла успешно, false если произошла ошибка
 */
bool GameManager::LoadGameSequenceFromEEPROM(int address)
{
#ifdef DEBUG_LOG
    Serial.println();
    Serial.println("Start reading sequence from EEPROM");
    Serial.print("Code address: ");
    Serial.println(address);
#endif

    // Первый байт содержит количество элементов в последовательности
    int numElements = EEPROM[address];

    // Проверяем, что количество элементов корректное
    if (!numElements || numElements > MAX_SEQUENCE_LENGTH)
    {
#ifdef DEBUG_LOG
        Serial.println("ERROR: sequence is empty or more than MAX_SEQUENCE_LENGTH (");
        Serial.print(MAX_SEQUENCE_LENGTH);
        Serial.print(')');
        Serial.println();
#endif
        return false;
    }

    // Очищаем текущую последовательность
    m_GameSequence.Clear();

    // Загружаем каждый элемент последовательности
    for (int i = 0; i < numElements; ++i)
        m_GameSequence.AddValue(EEPROM[address + i + 1]);

#ifdef DEBUG_LOG
    Serial.print("Loaded Data ");
    for (int i = 0; i < m_GameSequence.Length(); ++i)
        Serial.print(m_GameSequence.GetValue(i));
    Serial.println();
#endif
    return true;
}

/**
 * Основной цикл менеджера игры
 * Вызывает метод Run текущего состояния игры
 */
void GameManager::Run()
{
    // Если текущее состояние установлено, выполняем его цикл
    if (m_CurrentState)
        m_CurrentState->Run();
}