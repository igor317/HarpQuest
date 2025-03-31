/**
 * Mp3Player.h - Класс для работы с MP3-плеером DFPlayer Mini
 * 
 * Этот статический класс предоставляет простой интерфейс для 
 * управления MP3-плеером DFPlayer Mini, подключенным к Arduino.
 * Он позволяет инициализировать плеер, устанавливать громкость,
 * воспроизводить звуковые файлы и ждать их завершения.
 */

//#include "DFPlayer_Mini_Mp3.h>

#ifndef MP3PLAYER_H
#define MP3PLAYER_H

#include "config.h"
#include "DFPlayer_Mini_Mp3.h"

class Mp3Player
{
private:
    // Пин, подключенный к выходу BUSY плеера (показывает, воспроизводится ли звук)
    static int m_BusyPin;
public:
    /**
     * Инициализирует MP3-плеер
     * 
     * @param hserial последовательный порт для связи с плеером
     * @param busyPin пин, подключенный к выходу BUSY плеера
     */
    static void Init(HardwareSerial& hserial, int busyPin);
    
    /**
     * Устанавливает громкость воспроизведения
     * 
     * @param volume уровень громкости (от 0 до 30)
     */
    static void SetVolume(uint8_t volume);
    
    /**
     * Воспроизводит звуковой файл по его номеру
     * 
     * @param sampleId номер звукового файла (1.mp3 = 1, 2.mp3 = 2 и т.д.)
     * @param force если true, то останавливает текущее воспроизведение и начинает новое
     * @return true если воспроизведение началось, false если уже что-то воспроизводится и force=false
     */
    static bool PlaySample(uint16_t sampleId, bool force = false);
    
    /**
     * Ожидает завершения воспроизведения текущего звукового файла
     * Блокирует выполнение программы до окончания воспроизведения
     */
    static void WaitUntilFinish();
};

#endif
