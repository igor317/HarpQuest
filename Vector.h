/**
 * Vector.h - Динамический массив для Arduino
 * 
 * Этот класс представляет собой упрощенную реализацию динамического массива,
 * аналогичного std::vector из стандартной библиотеки C++. Он автоматически
 * расширяется при добавлении новых элементов и позволяет работать с массивами
 * без необходимости ручного управления памятью.
 * 
 * В проекте HarpQuest этот класс используется для хранения:
 * - Функций обратного вызова в Button для обработки нажатий
 * - Элементов последовательностей в Sequence
 * - Других коллекций, где нужно динамическое количество элементов
 * 
 * @tparam T тип элементов в массиве
 */

#ifndef VECTOR_H
#define VECTOR_H

template <class T>
class Vector
{
private:
	// Максимальный размер массива (вместимость)
	int m_MaxSize;
	
	// Текущее количество элементов в массиве
	int m_CurrentSize;
	
	// Указатель на массив данных
	T* m_Array;
public:
	/**
	 * Конструктор по умолчанию
	 * Создает пустой вектор с начальной вместимостью 2 элемента
	 */
	Vector()
	{
		m_CurrentSize = 0;
		m_MaxSize = 2;
		m_Array = new T[m_MaxSize];
	}
	
	/**
	 * Деструктор
	 * Освобождает память, выделенную под массив
	 */
	~Vector()
	{
		//Clear();
		delete[] m_Array;
	}

	/**
	 * Добавляет новый элемент в конец массива
	 * Если массив заполнен, его размер автоматически увеличится вдвое
	 * 
	 * @param element элемент для добавления
	 * 
	 * Пример использования:
	 * ```
	 * Vector<int> numbers;
	 * numbers.Add(10);  // Добавляем число 10
	 * numbers.Add(20);  // Добавляем число 20
	 * ```
	 */
	void Add(T element)
	{
		// Если текущий размер достиг максимального, увеличиваем массив
		if (m_CurrentSize >= m_MaxSize)
		{
			// Удваиваем максимальный размер
			m_MaxSize *= 2;
			
			// Создаем новый массив большего размера
			T* subArray = new T[m_MaxSize];
			
			// Копируем все элементы в новый массив
			for (int i = 0; i < m_CurrentSize; ++i)
			{
				subArray[i] = m_Array[i];
				//m_Array[i] = nullptr;
			}
			
			// Освобождаем память старого массива
			delete[] m_Array;
			
			// Сохраняем указатель на новый массив
			m_Array = subArray;
			subArray = nullptr;
		}
		
		// Добавляем новый элемент и увеличиваем счетчик размера
		m_Array[m_CurrentSize++] = element;
	}

	/**
	 * Удаляет элемент по указанному индексу
	 * 
	 * @param index индекс элемента для удаления
	 * 
	 * Пример использования:
	 * ```
	 * Vector<int> numbers;
	 * numbers.Add(10);
	 * numbers.Add(20);
	 * numbers.Add(30);
	 * numbers.Erase(1);  // Удаляем число 20 (индекс 1)
	 * ```
	 */
	void Erase(int index)
	{
		// Проверяем, что индекс находится в допустимом диапазоне
		if (index < 0 || index > m_CurrentSize - 1)
			return;

		// Если удаляем последний элемент, просто очищаем массив
		if (m_CurrentSize == 1)
		{
			Clear();
			return;
		}
		//m_Array[index] = nullptr;

		// Уменьшаем размер массива
		m_CurrentSize -= 1;
		
		// Создаем новый массив без удаляемого элемента
		T* subArray = new T[m_MaxSize];
		
		// Копируем элементы в новый массив, пропуская удаляемый
		for (int i = 0; i < m_CurrentSize; ++i)
		{
			subArray[i] = m_Array[(i < index) ? i : i + 1];
			//m_Array[i] = nullptr;
		}
		
		// Освобождаем память старого массива
		delete[] m_Array;
		
		// Сохраняем указатель на новый массив
		m_Array = subArray;
		subArray = nullptr;
	}

	/**
	 * Возвращает текущее количество элементов в массиве
	 * 
	 * @return количество элементов
	 * 
	 * Пример использования:
	 * ```
	 * Vector<int> numbers;
	 * numbers.Add(10);
	 * numbers.Add(20);
	 * int count = numbers.Size();  // count = 2
	 * ```
	 */
	int Size()
	{
		return m_CurrentSize;
	}

	/**
	 * Очищает массив, удаляя все элементы
	 * Сбрасывает размер до начального (2 элемента)
	 * 
	 * Пример использования:
	 * ```
	 * Vector<int> numbers;
	 * numbers.Add(10);
	 * numbers.Add(20);
	 * numbers.Clear();  // Массив пуст, размер = 0
	 * ```
	 */
	void Clear()
	{
		// Освобождаем память
		delete[] m_Array;
		
		// Сбрасываем параметры до начальных
		m_MaxSize = 2;
		m_CurrentSize = 0;
		
		// Создаем новый пустой массив
		m_Array = new T[m_MaxSize];
	}

	/**
	 * Оператор доступа к элементу по индексу
	 * 
	 * @param index индекс элемента
	 * @return ссылка на элемент с указанным индексом
	 * 
	 * Пример использования:
	 * ```
	 * Vector<int> numbers;
	 * numbers.Add(10);
	 * numbers.Add(20);
	 * int value = numbers[1];  // value = 20
	 * numbers[0] = 15;         // Изменяем первый элемент
	 * ```
	 */
	T& operator[](int const& index)
	{
		//if (index < 0 || index > m_CurrentStep - 1)
		//	return;
		return m_Array[index];
	}
};
#endif