#pragma once

#include <iostream>
#include "int_types_with_width.h"

/* A simple stack with fixed size */
template<typename T>
class TSimpleStack
{
public:
	TSimpleStack(u32 N)
	{
		capacity = N;
		data = new T[N];
	}
	~TSimpleStack()
	{
		delete[] data;
	}
	T* data{ nullptr };
	u32 Size() { return size; };
	u32 size{ 0 };
	u32 capacity{ 0 };
	void Push(const T& val)
	{
		if (size == capacity)
			throw("Full stack. Cannot push.");
		data[size++] = val;
	}
	T Pop()
	{
		if (size == 0)
			throw("Empty stack, cannot pop.");
		return std::move(data[(size--) - 1]);
	}
	T Peek()
	{
		if (size == 0)
			throw("Empty stack, cannot pop.");
		return data[size - 1];
	}
	bool Empty()
	{
		return size == 0;
	}
	void Print()
	{
		for (u32 i = 0; i < size; i++)
		{
			cout << data[i] << " ";
		}
		cout << endl;
	}

};
template<typename T>
TSimpleStack<T> sortSimpleStackInAscendingOrder(TSimpleStack<T>& stack)
{
	TSimpleStack<T> r{ stack.Size() }; // this has a same size as before
	while (!stack.Empty())
	{
		auto tmp = stack.Pop();
		while (!r.Empty() && r.Peek() > tmp)
		{
			stack.Push(r.Pop());
		}

		r.Push(tmp);
	}
	return r;
}

/*move element from one simple stack to another*/
template<typename T>
static inline void moveElement(TSimpleStack<T>& from, TSimpleStack<T>& to)
{
	to.Push(from.Pop());
}

/*classic problem of handling rods*/
template<typename T>
static inline void handleRods(TSimpleStack<T>& from, TSimpleStack<T>& mid, TSimpleStack<T>& to, u32 _size)
{
	if (_size == 0)
		return;
	else if (_size == 1)
	{
		moveElement(from, to);
		return;
	}
	else
	{
		handleRods(from, to, mid, _size - 1);
		moveElement(from, to);
		handleRods(mid, from, to, _size - 1);
		return;
	}
}

/* Size changable stack */
template<typename T>
class TStack
{
public:
	TStack() = default;
	TStack(u32 capacity) { reserve(capacity); }
	virtual ~TStack()
	{
		clear();
	};

	u32 m_size{ 0 };
	u32 m_capacity{ 0 };

	T* m_pData{ nullptr };
	void reserve(u32 capacity)
	{
		if (capacity > m_capacity)
		{
			auto pNewData = new T[capacity];
			m_capacity = capacity;
			if (m_pData) // we have old data
			{
				//copy old to new place
				for (u32 i = 0; i < m_size; i++)
				{
					pNewData[i] = std::move(m_pData[i]);
				}
				delete[] m_pData;
			}
			m_pData = pNewData;
		}
	}

	int size() { return m_size; };
	bool isEmpty() { return m_size == 0; };

	T Pop()
	{
		if (isEmpty())
			throw("Nothing to pop.");
		auto tmp = std::move(m_pData[m_size]);
		m_size--;
		return tmp;
	}

	// this function returns returns 0 if found(will not put it as duplicate) and return 1 if insert
	void Push(T&& val)
	{
		if (m_capacity <= m_size + 1)
			reserve((m_size + 1) * 2);
		m_pData[m_size]


	}



	void clear()
	{

	}

	void print()
	{

	}

};


/* using a queque with two stacks*/
template<typename T>
class TQueueUsingTwoStacks
{
public:
	TQueueUsingTwoStacks(u32 N)
	{
		pS1 = new TSimpleStack<T>(N);
		pS2 = new TSimpleStack<T>(N);
	};
	~TQueueUsingTwoStacks()
	{
		clear();
	};
	void clear()
	{
		delete pS1;
		delete pS2;
	};
	TSimpleStack<T>* pS1{ nullptr }; //newest at top
	TSimpleStack<T>* pS2{ nullptr }; //oldest at top
	void Push(T&& val)
	{
		if (pS1->full())
			throw("full stacks");
		pS1->Push(std::forward<T>(val));
	}
	T Pop()
	{
		if (pS2->empty())
		{
			if (pS1->empty())
				throw("Nothing to pop.");
			while (!pS1->empty() && !pS2->full())
				pS2->Push(pS1->Pop());
		}
		auto tmp = pS2->Pop();
		if (pS2->empty())
		{
			while (!pS1->empty() && !pS2->full())
				pS2->Push(pS1->Pop());
		}
		return tmp;
	}
};