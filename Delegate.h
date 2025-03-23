#ifndef DELEGATE_H
#define DELEGATE_H
#define CreateEventHandler(class,func) new EventMethod<class>(this,&class::func)
#define CreateEventHandlerFunction(func) new EventFunction(func)

#include "Vector.h"
class EventFunc
{
public:
	virtual ~EventFunc() { }
	virtual void exec() = 0;
};

class EventFunction : public EventFunc
{
private:
	void(*func)();
public:
	EventFunction(void(*function)())
	{
		func = function;
	}

	~EventFunction()
	{
		func = nullptr;
	}

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

template<typename T>
class EventMethod : public EventFunc
{
private:
	T* classObj;
	void (T::*method)();
public:
	EventMethod(T* t, void (T::*method)())
	{
		classObj = t;
		this->method = method;
	}
	~EventMethod()
	{
		classObj = nullptr;
		method = nullptr;
	}

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

class Delegate
{
public:
	Vector<EventFunc*> m_Functions;
public:
	Delegate()
	{

	}

	Delegate(EventFunc* func)
	{
		if (func != nullptr)
			m_Functions.Add(func);
	}

	~Delegate()
	{
		Free();
	}

	void Free()
	{
		while (m_Functions.Size() > 0)
		{
			delete m_Functions[0];
			m_Functions.Erase(0);
		}
	}

	void Exec()
	{				
		for (int i = 0; i < m_Functions.Size(); ++i)
			//if (m_Functions[i] != NULL)
				m_Functions[i]->exec();
	}

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