/*
 * chaining_hash_unordered_map.h
 *
 *  Created on: Jan 8, 2017
 *      Author: Yang
 */

#ifndef CHAINING_HASH_UNORDERED_MAP_H_
#define CHAINING_HASH_UNORDERED_MAP_H_

#include "seq_search_unordered_map.h"
#include <typeinfo>

template<typename TKey, typename TVal>
class TChaining_Hash_Unordered_Map
{
public:
	explicit TChaining_Hash_Unordered_Map(int _nSlots):m_nSlots(_nSlots)
	{
		m_hash_tables = new TSeq_Search_Unordered_Map<TKey, TVal>[m_nSlots] { };
	};

	virtual ~TChaining_Hash_Unordered_Map()
	{
		clear();
		delete [] m_hash_tables;
	};

	int m_size { 0 };
	int m_nSlots { 0 };
	TSeq_Search_Unordered_Map<TKey, TVal>* m_hash_tables;
	int size() { return m_size;};
	bool isEmpty() { return m_size == 0;};

	int getHash(TKey key)
	{
			return key % m_nSlots;
	}
	TVal* get(TKey key)
	{
		return m_hash_tables[getHash(key)].get(key);
	}

	// this function returns -1 if full, returns 0 if replace and return 1 if insert
	int put(TKey key, TVal val)
	{
		return m_hash_tables[getHash(key)].put(key, val);
	}

	void remove(TKey key)
	{
		m_hash_tables[getHash(key)].remove(key);
	}

	void clear()
	{
		for (int i = 0; i < m_nSlots; i++)
			m_hash_tables[i].clear();
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



#endif /* CHAINING_HASH_UNORDERED_MAP_H_ */
