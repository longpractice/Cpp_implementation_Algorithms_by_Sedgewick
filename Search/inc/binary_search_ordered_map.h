/*
 *
 *  Created on: Jan 1, 2017
 *      Author: Yang
 */

#ifndef BINARY_SEARCH_ORDERED_MAP_H_
#define BINARY_SEARCH_ORDERED_MAP_H_

// This is the binary search version(using dynamic array as underlining container) of map
// It does not have efficient insertion and deletion, it is only efficient for searching
template<typename TKey, typename TVal>
class TBinary_Search_Ordered_Map
{
public:

	explicit TBinary_Search_Ordered_Map(int _capacity):m_capacity(_capacity), m_pairs(new TPair[_capacity])
	{
		for (int i = 0; i < m_capacity; i++)
		{
			m_pairs[i].pKey = nullptr;
			m_pairs[i].pVal = nullptr;
		}
	};

	virtual ~TBinary_Search_Ordered_Map()
	{
		clear();
		delete [] m_pairs;
	};

	int m_capacity { 0 };
	int m_size { 0 };
	struct TPair
	{
		TKey* pKey;
		TVal* pVal;
	};
	TPair* m_pairs { nullptr };
	int size() { return m_size;};
	bool isEmpty() { return m_size == 0;};
	TVal* get(TKey key)
	{
		if(isEmpty()) return nullptr;
		auto index = rank(key);
		if(index < m_size && *(m_pairs[index].pKey) == key)
			return m_pairs[index].pVal;
		else
			return nullptr;
	}
	// this function makes sure that if key <= keys[lo], we return lo, and if key > keys[hi], we put it at hi+1
	int rank(TKey key, int lo, int hi)
	{
		if(hi < lo) return lo;
		int mid = lo + (hi - lo)/2;
		auto midKey = *(m_pairs[mid].pKey);
		if (key < midKey)
			return rank(key, lo, mid - 1);
		else if (key > midKey)
			return rank(key, mid + 1, hi);
		else
			return mid;
	}
	int rank(TKey key)
	{
		return rank(key, 0, m_size - 1);
	}
	// this function returns -1 if full, returns 0 if replace and return 1 if insert
	int put(TKey key, TVal val)
	{
		auto index = rank(key);
		// an update
		if(index < m_size && *(m_pairs[index].pKey) == key)
		{
			*(m_pairs[index].pVal) = val;
			return 0; // an update
		}
		// in case it is a insert we have to move the ones behind, if it is full we return -1
		if (m_size == m_capacity)
			return -1;

		for(int iTarget = m_size; iTarget > index; iTarget--)
		{
			m_pairs[iTarget] = m_pairs[iTarget - 1];
		}


		m_size++;

		// now we have made the space for the new pair
		m_pairs[index].pKey = new TKey;
		*(m_pairs[index].pKey) = key;

		m_pairs[index].pVal = new TVal;
		*(m_pairs[index].pVal) = val;
	}

	void remove(TKey key)
	{
		auto index = rank(key);
		// an update
		if(index < m_size && *(m_pairs[index].pKey) == key)
		{
			delete m_pairs[index].pKey;
			delete m_pairs[index].pVal;

			//shift what is behind to here
			for(int iTarget = index; iTarget < m_size - 1; iTarget++)
				m_pairs[iTarget] = m_pairs[iTarget + 1];

			// set the last one to nullptr
			m_pairs[m_size - 1].pKey = nullptr;
			m_pairs[m_size - 1].pVal = nullptr;
			m_size--;
		}
		else
			return; //we could not find a key
	}
	void clear()
	{
		//delete all the automatically allocated keys and vals
		for (int i = 0; i < m_size; i++)
		{
			delete m_pairs[i].pKey;
			delete m_pairs[i].pVal;
			m_size = 0;
		}
	}
// I will do this later
	//	typedef TPair value_type;
//	typedef TPair* pointer;
//	typedef const TPair* const_pointer;
//	typedef TPair& reference;
//	typedef const TPair& const_reference;
//	typedef size_t size_type;
//	typedef TPair* difference_type;




};


#endif /* BINARY_SEARCH_ORDERED_MAP_H_ */
