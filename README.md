﻿# HarpQuest - Волшебная арфа

## 🎵 Что это такое?

HarpQuest - это удивительная интерактивная игрушка на основе платы Arduino, которая имитирует волшебную арфу! Чтобы открыть "магический замок", игрок должен нажать на правильную последовательность струн. Если последовательность правильная - замок открывается!

![Схема арфы](https://i.ibb.co/8DgKfCx/harp-quest-scheme.png)

## 🎮 Как играть?

1. На арфе есть 5 струн (на самом деле - фоторезисторов)
2. Нужно нажимать на струны в правильной последовательности
3. Арфа будет воспроизводить звуки при нажатии на струны
4. Когда ты введешь полную последовательность, игра проиграет все звуки и проверит, правильно ли ты нажимал
5. Если последовательность правильная - загорится светодиод и откроется замок!
6. Если последовательность неправильная - игра сбросится, и ты сможешь начать заново

## 🔧 Компоненты

Для создания HarpQuest нужны:
- Плата Arduino Uno или аналогичная
- 5 фоторезисторов (для "струн" арфы)
- 5 резисторов на 10 кОм
- Кнопка игрока
- Кнопка администратора
- MP3-плеер DFPlayer Mini
- Динамик для воспроизведения звуков
- Электромагнитный замок или реле
- SD-карта с звуковыми файлами
- Провода и макетная плата

## 🛠️ Как это работает?

### Основные режимы:
1. **Нормальный режим** - основной режим игры, где игрок пытается повторить правильную последовательность
2. **Режим калибровки** - используется для настройки чувствительности струн или изменения правильной последовательности
3. **Режим завершения** - активируется при успешном вводе правильной последовательности, открывает замок

### Система струн:
- Каждая "струна" на самом деле является фоторезистором
- Когда игрок закрывает фоторезистор рукой, меняется его сопротивление
- Arduino определяет это изменение и считает, что струна была "задета"
- Каждая струна имеет свой номер (от 1 до 5)

### Последовательность:
- Правильная последовательность струн хранится в EEPROM (памяти Arduino)
- По умолчанию, это последовательность 1-2-3
- В режиме калибровки можно изменить эту последовательность

### Звуки:
- Каждая струна издает свой звук при нажатии
- MP3-плеер DFPlayer Mini используется для воспроизведения звуков
- На SD-карте должны быть файлы с именами:
  - 0001.mp3, 0002.mp3, 0003.mp3, 0004.mp3, 0005.mp3 - звуки для каждой струны
  - 0007.mp3 - звук начала калибровки
  - 0008.mp3 - звук завершения калибровки

## 👨‍💻 Настройка

### Кнопки:
- **Обычная кнопка**: нажатие и удержание в течение 2 секунд переводит арфу в режим калибровки
- **Кнопка администратора**: нажатие и удержание в течение 1 секунды сразу открывает замок (для проверки или экстренных случаев)

### Параметры (config.h):
В файле config.h можно настроить:
- Чувствительность струн (HARPSTIRNG_THRESHOLD)
- Время удержания кнопок
- Громкость звука
- Пины подключения
- И многое другое!

## 🧩 Структура проекта

- **HarpQuest.ino** - основной файл проекта
- **config.h** - файл с настройками
- **GameManager** - управляет всей игрой
- **HarpString** - класс для работы со "струнами" арфы
- **NormalGameState** - обычное состояние игры
- **CalibrationState** - режим калибровки
- **FinishGameState** - режим завершения
- **Sequence** - класс для хранения и сравнения последовательностей
- **Button** - класс для работы с кнопками
- **Mp3Player** - класс для работы с MP3-плеером

## 🚀 Создание своей волшебной арфы

1. Соберите схему подключения, как показано на рисунке выше
2. Загрузите код на Arduino
3. Запишите звуковые файлы на SD-карту с правильными именами
4. Поместите SD-карту в MP3-плеер
5. Подключите питание
6. Настройте чувствительность струн в режиме калибровки
7. Наслаждайтесь игрой!

## 🧙 Секретные возможности для родителей

1. **Изменение последовательности**: в режиме калибровки нажмите струны в нужной последовательности, и эта последовательность станет новой правильной последовательностью
2. **Быстрое открытие замка**: с помощью кнопки администратора можно быстро открыть замок
3. **Настройка чувствительности**: в режиме калибровки можно настроить чувствительность струн

## 🛠️ Устранение неполадок

- **Струны не срабатывают**: проверьте чувствительность в файле config.h или используйте режим калибровки
- **Нет звука**: проверьте подключение MP3-плеера и наличие файлов на SD-карте
- **Замок не открывается**: проверьте подключение пина LOCKER_PIN

## 🧩 Дополнительные возможности

- Добавьте светодиоды для подсветки струн
- Создайте красивый корпус для арфы
- Запишите свои собственные звуки для струн
- Добавьте режим "обучения", где арфа будет показывать, какую струну нажать следующей

Желаем вам волшебной игры с арфой HarpQuest! 🎵✨
