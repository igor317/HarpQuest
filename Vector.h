#ifndef VECTOR_H
#define VECTOR_H

template <class T>
class Vector
{
private:
	int m_MaxSize;
	int m_CurrentSize;
	T* m_Array;
public:
	Vector()
	{
		m_CurrentSize = 0;
		m_MaxSize = 2;
		m_Array = new T[m_MaxSize];
	}
	~Vector()
	{
		//Clear();
		delete[] m_Array;
	}

	void Add(T element)
	{
		if (m_CurrentSize >= m_MaxSize)
		{
			m_MaxSize *= 2;
			T* subArray = new T[m_MaxSize];
			for (int i = 0; i < m_CurrentSize; ++i)
			{
				subArray[i] = m_Array[i];
				//m_Array[i] = nullptr;
			}
			delete[] m_Array;
			m_Array = subArray;
			subArray = nullptr;
		}
		m_Array[m_CurrentSize++] = element;
	}

	void Erase(int index)
	{
		if (index < 0 || index > m_CurrentSize - 1)
			return;

		if (m_CurrentSize == 1)
		{
			Clear();
			return;
		}
		//m_Array[index] = nullptr;

		m_CurrentSize -= 1;
		T* subArray = new T[m_MaxSize];
		for (int i = 0;i < m_CurrentSize;++i)
		{
			subArray[i] = m_Array[(i < index) ? i : i + 1];
			//m_Array[i] = nullptr;
		}
		delete[] m_Array;
		m_Array = subArray;
		subArray = nullptr;
	}

	int Size()
	{
		return m_CurrentSize;
	}

	void Clear()
	{
		delete[] m_Array;
		m_MaxSize = 2;
		m_CurrentSize = 0;
		m_Array = new T[m_MaxSize];
	}

	T& operator[](int const& index)
	{
		//if (index < 0 || index > m_CurrentStep - 1)
		//	return;
		return m_Array[index];
	}
};
#endif