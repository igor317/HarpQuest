#ifndef CONFIG_H
#define CONFIG_H

#define DEBUG_LOG   // Раскомментировать для вывода отладки в последовательный порт

#define EEPROM_DATA_START_ADDRESS 0     // Адрес записи последовательности

#define CALIBRATION_MODE_TIMEOUT 2000   // Время удержания кнопки для перехода в режим калибровки
#define ADMIN_BUTTON_TIMEOUT 1000       // Время через которое сработает кнопка админа

#define HARPSTRING_HIGHLIGHTED_DEFAULT    // Закоментировать, если по умолчанию фоторезисторы засвечены

#define HARPSTIRNG_THRESHOLD  50  // Порог срабатывания струны
#define NUM_HARPSTRINGS 5   // Числи струн

#define BUTTON_PIN  8       // Пин кнопки
#define ADMIN_BUTTON_PIN 7  // Пин кнопки админа

#define LOCKER_PIN 13       // Пин замка
#define MP3_BUSY_PIN 2      // Пин Busy

#define SOUND_VOLUME 25     // Громкость звука

#define MAX_SEQUENCE_LENGTH 20    // Максимальная длина последовательности

#define WAIT_AFTER_END_SEQUENCE 1000    // Ожидает перед тем как проиграть введенную последовательность

#define SAMPLE_START_CALIBRATION 7    // Номер сэмпла который проиграется при начале калибровки
#define SAMPLE_END_CALIBRAION 8       // Номер сэмпла который проиграется при завершении калибровки

#define END_CALIBRATION_INTERVAL 5000   // Если в течение этого времени не поступит новая команда, то калибровка закончится 

#define FINISH_GAME_TIMEOUT 5000    // Время, через которое после победы игра возвращается в нормальное состояние
#endif