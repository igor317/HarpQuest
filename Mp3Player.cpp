#include "Mp3Player.h"

// Статическая переменная для хранения пина BUSY
int Mp3Player::m_BusyPin;

/**
 * Инициализирует MP3-плеер
 * Настраивает пин BUSY и устанавливает связь с плеером через Serial
 * 
 * @param hserial последовательный порт для связи с плеером (обычно Serial)
 * @param busyPin пин, подключенный к выходу BUSY плеера
 */
void Mp3Player::Init(HardwareSerial& hserial, int busyPin)
{
    // Сохраняем номер пина BUSY
    m_BusyPin = busyPin;

    // Настраиваем пин BUSY как вход
    pinMode(m_BusyPin, INPUT);

    // Инициализируем связь с плеером
    hserial.begin(9600);
    
    // Настраиваем библиотеку DFPlayer_Mini_Mp3
    mp3_set_serial(hserial);
}

/**
 * Устанавливает громкость воспроизведения
 * 
 * @param volume уровень громкости (от 0 до 30)
 */
void Mp3Player::SetVolume(uint8_t volume)
{
    // Устанавливаем громкость через библиотеку DFPlayer_Mini_Mp3
    mp3_set_volume(volume); 
}

/**
 * Воспроизводит звуковой файл по его номеру
 * 
 * @param sampleId номер звукового файла (1.mp3 = 1, 2.mp3 = 2 и т.д.)
 * @param force если true, то останавливает текущее воспроизведение и начинает новое
 * @return true если воспроизведение началось, false если уже что-то воспроизводится и force=false
 */
bool Mp3Player::PlaySample(uint16_t sampleId, bool force)
{
    // Проверяем, свободен ли плеер (HIGH на пине BUSY) или требуется принудительное воспроизведение
    if (digitalRead(m_BusyPin) || force)
    {
        // Начинаем воспроизведение указанного файла
        mp3_play(sampleId);
        
        // Даем немного времени на начало воспроизведения
        delay(200);
        return true;
    }
    return false;
}

/**
 * Ожидает завершения воспроизведения текущего звукового файла
 * Блокирует выполнение программы до окончания воспроизведения
 */
void Mp3Player::WaitUntilFinish()
{
    // Ждем, пока на пине BUSY не появится HIGH (означает, что воспроизведение завершено)
    while (!digitalRead(m_BusyPin)) {}
}