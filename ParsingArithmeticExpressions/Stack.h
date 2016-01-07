#pragma once

template<typename T>
class Stack
{
    // Количество элементов, под которое в стеке выделена память.
    unsigned int m_capacity;

    // Количество элементов в стеке.
    unsigned int m_size;

    // Массив для хранения данных.
    T* m_stack;

public:

	Stack();
    Stack(const Stack<T>& stack);

    ~Stack();

    Stack<T>& operator=(const Stack<T>& right);
	
    // Очистка стека.
    void Clear();

    // Проверка существования элементов в стеке.
    bool IsEmpty();

    // Просмотр элемента в вершине стека.
    T Peek();

    // Получение элемента из стека.
    T Pop();

    // Добавление элемента в стек.
    void Push(const T value);
	
    // Получение количества элементов в стеке.
    unsigned int GetSize();
};


template<class T>
Stack<T>::Stack() :
m_capacity(20U),
m_size(0U),
m_stack(new T[10])
{
}

template<class T>
Stack<T>::Stack(const Stack<T>& stack) :
m_capacity(stack.m_capacity),
m_size(stack.m_size),
m_stack(new T[stack.m_capacity])
{
	for (unsigned int i = 0U; i < stack.m_size; ++i)
	{
		m_stack[i] = stack.m_stack[i];
	}
}

template<class T>
Stack<T>::~Stack()
{
	delete[] m_stack;
}

template<class T>
Stack<T> & Stack<T>::operator=(const Stack<T> & right)
{
	if (this != &right)
	{
		// Очистка стека.
		delete[] m_stack;

		m_capacity = right.m_capacity;
		m_size = right.m_size;
		m_stack = new T[right.m_capacity];

		for (unsigned int i = 0U; i < right.m_size; ++i)
		{
			m_stack[i] = right.m_stack[i];
		}
	}

	return *this;
}

template<class T>
void Stack<T>::Clear()
{
	// Эффективная "очистка" стека (данные в массиве все еще существуют, но методы класса, ориентированные на работу с 
	// вершиной стека, будут их игнорировать).
	m_size = 0U;
}

template<class T>
unsigned int Stack<T>::GetSize()
{
	// Количество присутствующих в стеке элементов.
	return m_size;
}

template<class T>
bool Stack<T>::IsEmpty()
{
	return m_size == 0U;
}

template<class T>
T Stack<T>::Peek()
{
	T result = -1;

	// Возврат верхнего элемента, если в стеке есть элементы.
	if (!IsEmpty())
	{
		result = m_stack[m_size - 1U];
	}

	return result;
}

template<class T>
T Stack<T>::Pop()
{
	T result = -1;

	// Возврат верхнего элемента и уменьшение размера, если в стеке есть элементы.
	if (!IsEmpty())
	{
		result = m_stack[m_size - 1U];

		--m_size;
	}

	return result;
}

template<class T>
void Stack<T>::Push(const T value)
{
	if (m_capacity == m_size)
	{
		m_capacity += 2U;

		T* copy = new T[m_capacity];

		for (unsigned int i = 0U; i < m_size; ++i)
		{
			copy[i] = m_stack[i];
		}

		delete[] m_stack;

		m_stack = copy;
	}

	// Добавление нового элемента.
	m_stack[m_size] = value;

	// Увеличение размера стека.
	++m_size;
}