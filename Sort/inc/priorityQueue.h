
#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_
#include <iostream>

//this priority queue uses a binary heap data structure, note that
// you could change the less() member method for configuring a max priority queue or a min priority queue
template<typename T>
class TPriorityQueue
{
public:
	TPriorityQueue(int _capacity):m_capacity(_capacity), m_items(new T[_capacity + 1]){};
	virtual ~TPriorityQueue()
	{
		delete [] m_items;
	};
	bool less(int a, int b)
	{
		// if < sign is used, the max will be removed in delMax and vice virza
		return m_items[a] < m_items[b];
	}
	void exch(int a, int b)
	{
		auto tmp = m_items[a];
		m_items[a] = m_items[b];
		m_items[b] = tmp;
	}
	T* m_items;
	int m_capacity; // the size of the array is m_capacity + 1
	int m_size{ 0 }; // the max index is however m_size

	void swim(int index)
	{
		while (index > 1 && less(index / 2, index))
		{
			exch(index, index / 2);
			index /= 2;
		}
	}

	void sink(int idx)
	{
		while (idx * 2 <= m_size) // right child index is no bigger than the max index
		{
			int j = 2 * idx; // this the left child
			if (j < m_size && less(j, j + 1)) j++; // we always compare with the larger one
			if (!less(idx, j)) break;
			exch(idx, j);	// so we exchange with the bigger of the child
			idx = j;
		}
	}
	bool insert(T item)
	{
		if (m_size >= m_capacity)
			return false; // we could not absorb any more
		m_items[++m_size] = item; //put the new at last and then swim it
		swim(m_size);
		return true;
	}
	T delMax()
	{
		T max = m_items[1];
		m_items[1] = m_items[m_size]; // move the last one to the top and the sink it
		m_size--;
		sink(1);
		return max;
	}
	int size()
	{
		return m_size;
	}

	void printMe()
	{
		int layer = 0;
		int count = 1;
		while(count <= m_size)
		{
			for(int i = 0; i < (1 >> layer) && count <= m_size; i++)
				std::cout << m_items[count++] << " ";
			layer++;
			std::cout << "\n";
		}
	}
};



#endif /* PRIORITYQUEUE_H_ */
