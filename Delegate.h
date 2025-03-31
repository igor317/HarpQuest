/**
 * Delegate.h - Механизм делегатов и обработчиков событий
 * 
 * Этот файл содержит реализацию механизма делегатов для Arduino,
 * позволяющего работать с функциями как с объектами. Делегаты позволяют
 * создавать события и назначать обработчики, которые будут вызваны при
 * наступлении события.
 * 
 * Основные компоненты:
 * - EventFunc: базовый абстрактный класс для любой функции-обработчика
 * - EventFunction: класс для обычных функций
 * - EventMethod: шаблонный класс для методов классов
 * - Delegate: класс, хранящий список функций и позволяющий их вызывать
 * 
 * В проекте HarpQuest этот механизм используется для:
 * - Обработки нажатий кнопок
 * - Работы с таймаутами
 * - Создания событий завершения игры
 */

#ifndef DELEGATE_H
#define DELEGATE_H

/**
 * Макрос для создания обработчика из метода класса
 * 
 * @param class класс, метод которого будет использоваться как обработчик
 * @param func имя метода
 * @return новый объект EventMethod
 */
#define CreateEventHandler(class,func) new EventMethod<class>(this,&class::func)

/**
 * Макрос для создания обработчика из обычной функции или лямбда-выражения
 * 
 * @param func функция или лямбда-выражение
 * @return новый объект EventFunction
 */
#define CreateEventHandlerFunction(func) new EventFunction(func)

#include "Vector.h"

/**
 * Базовый абстрактный класс для всех типов функций-обработчиков
 * Определяет интерфейс, который должны реализовать все обработчики
 */
class EventFunc
{
public:
	/**
	 * Виртуальный деструктор
	 */
	virtual ~EventFunc() { }
	
	/**
	 * Абстрактный метод для выполнения функции
	 * Должен быть реализован в производных классах
	 */
	virtual void exec() = 0;
};

/**
 * Класс для работы с обычными функциями или лямбда-выражениями
 */
class EventFunction : public EventFunc
{
private:
	// Указатель на функцию без параметров и возвращаемого значения
	void(*func)();
public:
	/**
	 * Конструктор EventFunction
	 * 
	 * @param function указатель на функцию, которая будет вызываться
	 */
	EventFunction(void(*function)())
	{
		func = function;
	}

	/**
	 * Деструктор EventFunction
	 */
	~EventFunction()
	{
		func = nullptr;
	}

	/**
	 * Выполняет связанную функцию
	 */
	void exec()
	{
		func();
	}

	/*int Equal(IpEventFunc* f1)
	{
		if (this == f1)
			return 1;
		IpEventFunction* val = dynamic_cast<IpEventFunction*>(f1);
		if (val != NULL && ((IpEventFunction*)f1)->func == func)
			return 2;
		return 0;
	}*/
};

/**
 * Шаблонный класс для работы с методами классов
 * 
 * @tparam T тип класса, метод которого будет использоваться
 */
template<typename T>
class EventMethod : public EventFunc
{
private:
	// Указатель на объект класса
	T* classObj;
	
	// Указатель на метод класса
	void (T::*method)();
public:
	/**
	 * Конструктор EventMethod
	 * 
	 * @param t указатель на объект класса
	 * @param method указатель на метод класса
	 */
	EventMethod(T* t, void (T::*method)())
	{
		classObj = t;
		this->method = method;
	}
	
	/**
	 * Деструктор EventMethod
	 */
	~EventMethod()
	{
		classObj = nullptr;
		method = nullptr;
	}

	/**
	 * Выполняет связанный метод класса
	 */
	void exec()
	{
		(classObj->*method)();
	}

	/*int Equal(IpEventFunc* f1)
	{
		if (this == f1)
			return 1;
		IpEventMethod* m = dynamic_cast<IpEventMethod*>(f1);
		if ((m != NULL && ((IpEventMethod*)f1)->classObj == classObj
			&& ((IpEventMethod*)f1)->method == method))
			return 2;
		return 0;
	}*/
};

/**
 * Класс Delegate - контейнер для функций-обработчиков
 * Позволяет хранить несколько функций и вызывать их все одновременно
 */
class Delegate
{
public:
	// Вектор функций-обработчиков
	Vector<EventFunc*> m_Functions;
public:
	/**
	 * Конструктор по умолчанию
	 * Создает пустой делегат без обработчиков
	 */
	Delegate()
	{

	}

	/**
	 * Конструктор с одной функцией
	 * Создает делегат с одним обработчиком
	 * 
	 * @param func указатель на функцию-обработчик
	 */
	Delegate(EventFunc* func)
	{
		if (func != nullptr)
			m_Functions.Add(func);
	}

	/**
	 * Деструктор Delegate
	 * Освобождает память, занятую всеми обработчиками
	 */
	~Delegate()
	{
		Free();
	}

	/**
	 * Освобождает память, занятую всеми обработчиками
	 */
	void Free()
	{
		while (m_Functions.Size() > 0)
		{
			delete m_Functions[0];
			m_Functions.Erase(0);
		}
	}

	/**
	 * Выполняет все функции-обработчики
	 * 
	 * Пример использования:
	 * ```
	 * Delegate onButtonClick;
	 * onButtonClick += CreateEventHandlerFunction([]() { Serial.println("Button clicked!"); });
	 * onButtonClick.Exec();  // Выведет "Button clicked!"
	 * ```
	 */
	void Exec()
	{				
		for (int i = 0; i < m_Functions.Size(); ++i)
			//if (m_Functions[i] != NULL)
				m_Functions[i]->exec();
	}

	/**
	 * Проверяет, пуст ли делегат (нет ли обработчиков)
	 * 
	 * @return true если делегат не содержит функций, false в противном случае
	 */
	bool IsEmpty()
	{
		return (m_Functions.Size() > 0) ? false : true;
	}

	/*Delegate& operator= (EventFunc* func)
	{
		Free();
		if (func != nullptr)
			m_Functions.Add(func);
		return *this;
	}*/

	/**
	 * Оператор += добавляет новую функцию-обработчик в делегат
	 * 
	 * @param func указатель на функцию-обработчик
	 * @return ссылка на текущий делегат
	 * 
	 * Пример использования:
	 * ```
	 * Delegate onButtonClick;
	 * onButtonClick += CreateEventHandlerFunction([]() { Serial.println("Handler 1"); });
	 * onButtonClick += CreateEventHandlerFunction([]() { Serial.println("Handler 2"); });
	 * ```
	 */
	Delegate& operator+= (EventFunc* func)
	{
		if (func != nullptr)
			m_Functions.Add(func);
		return *this;
	}

	/*Delegate& operator+= (Delegate& delegate)
	{
		for (int i = 0;i<delegate.m_Functions.Size();++i)
			m_Functions.Add(delegate.m_Functions[i]);
		return *this;
	}*/

	/**
	 * Оператор () вызывает все функции-обработчики
	 * 
	 * Пример использования:
	 * ```
	 * Delegate onButtonClick;
	 * onButtonClick += CreateEventHandlerFunction([]() { Serial.println("Handler"); });
	 * onButtonClick();  // Вызовет все обработчики
	 * ```
	 */
	void operator()()
	{
		Exec();
	}

	/*IpDelegate& operator-= (IpEventFunc* func)
	{
		for (int i = 0; i < m_Functions.Size(); ++i)
		{
			int v = m_Functions[i]->Equal(func);
			if (v)
			{
				delete func;
				if (v == 2)
					delete m_Functions[i];
				m_Functions.Erase(i);
				break;
			}
		}
		return *this;
	}*/
};
#endif