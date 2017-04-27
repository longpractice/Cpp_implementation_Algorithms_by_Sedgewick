/*
 * seq_search_unordered_map.h
 *
 *  Created on: Jan 1, 2017
 *      Author: Yang
 */

#ifndef SEQ_SEARCH_UNORDERED_MAP_H_
#define SEQ_SEARCH_UNORDERED_MAP_H_

template<typename TKey, typename TVal>
class TSeq_Search_Unordered_Map
{
public:

	explicit TSeq_Search_Unordered_Map()
	{
	};

	virtual ~TSeq_Search_Unordered_Map()
	{
		clear();
	};

	int m_size { 0 };
	struct TPair
	{
		TKey* pKey;
		TVal* pVal;
	};
	struct TList
	{
		TPair pair;
		TList* next;
		TList* before;
	};

	TList* m_pHead { nullptr };
	TList* m_pTail { nullptr };
	int size() { return m_size;};
	bool isEmpty() { return m_size == 0;};
	TVal* get(TKey key)
	{
		auto p = m_pHead;
		while(p)
		{
			if(*(p->pair.pKey) == key)
				return p->pair.pVal;
			else
				p = p->next;
		}
		return nullptr;
	}
	// this function returns -1 if full, returns 0 if replace and return 1 if insert
	int put(TKey key, TVal val)
	{
		auto p = m_pHead;
		while(p)
		{
			if(*(p->pair.pKey) == key)
			{
				*(p->pair.pVal) = val;
				return 0;
			}
			else
				p = p->next;
		}

		// we could not really find it, put it at the head of the list
		m_size++;
		TList* pNewListItem = new TList;
		pNewListItem->pair.pKey = new TKey;
		*(pNewListItem->pair.pKey) = key;
		pNewListItem->pair.pVal = new TVal;
		*(pNewListItem->pair.pVal) = val;

		// so now next of the new is the old new
		pNewListItem->next = m_pHead;
		// so the before of the new is nothing
		pNewListItem->before = nullptr;

		//old head
		if (m_pHead)
		m_pHead->before = pNewListItem;
		m_pHead = pNewListItem;

		return 1;
	}

	void remove(TKey key)
	{
		auto p = m_pHead;
		while(p)
		{
			if(*(p->pair.pKey) == key)
			{
				delete p->pair.pKey;
				delete p->pair.pVal;

				if(p->before)
					p->before->next = p->next;
				if(p->next)
					p->next->before = p->before;

				delete p;
				m_size--;
				return;
			}
			p = p->next;
		}

		// we could not really find it, nothing to remove
		return;
	}
	void clear()
	{
		//delete all the automatically allocated keys and vals
		auto p = m_pHead;
		while(p)
		{
			delete p->pair.pKey;
			delete p->pair.pVal;
			auto tmp = p->next;
			delete p;
			p = tmp;
		}
		m_size = 0;
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

template<typename T>
class TBag
{
public:
	TBag() = default;
	virtual ~TBag()
	{
		clear();
	};

	int m_size{ 0 };

	struct TNode
	{
		T val;
		TNode* next;
	};

	TNode* m_pHead{ nullptr };

	int size() { return m_size; };
	bool isEmpty() { return m_size == 0; };

	T* get(T key)
	{
		auto p = m_pHead;
		while (p)
		{
			if (p->val == key)
				return &(p->val);
			else
				p = p->next;
		}
		return nullptr;
	}

	template<typename Func>
	T* get_if(Func f)
	{
		auto p = m_pHead;
		while (p)
		{
			if (f(p->val))
				return &(p->val);
			else
				p = p->next;
		}
		return nullptr;
	}

	// this function returns returns 0 if found(will not put it as duplicate) and return 1 if insert
	int put(T key)
	{
		if (get(key))
			return 0; // we could find it so we do not need to do anything

					  // we could not really find it, put it at the head of the list
		m_size++;
		TNode* pNewListItem = new TNode;
		pNewListItem->val = key;

		// so now next of the new is the old new
		pNewListItem->next = m_pHead;
		m_pHead = pNewListItem;
		return 1;
	}

	int remove(T key) //returns 1 if found, returns 0 if not found
	{
		auto p = m_pHead;
		decltype(p) p2p = nullptr;
		while (p)
		{
			if (p->val == key)
			{
				if (p2p)
					p2p->next = p->next;

				if (p == m_pHead)
					m_pHead = p->next;

				delete p;

				m_size--;
				return 1;
			}
			p2p = p;
			p = p->next;
		}
		// we could not really find it, nothing to remove
		return 0;
	}

	void clear()
	{
		//delete all the automatically allocated list members
		auto p = m_pHead;
		while (p)
		{
			auto tmp = p->next;
			delete p;
			p = tmp;
		}
		m_size = 0;
	}

	void print()
	{
		auto p = m_pHead;
		while (p)
		{
			std::cout << p->val << " ";
			p = p->next;
		}
		std::cout << std::endl;
		return;
	}
};

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
	void reserve(capacity)
	{
		if (capacity > m_capacity)
		{		
			auto pNewData = new T[capacity];
			m_capacity = capacity;
			if(m_pData) // we have old data
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

	T pop()
	{
		if (isEmpty())
			throw("Nothing to pop.");
		auto tmp = std::move(m_pData[m_size]);
		m_size--;
		return tmp;
	}

	// this function returns returns 0 if found(will not put it as duplicate) and return 1 if insert
	void push(T&& val)
	{
		if (m_capacity <= m_size + 1)
			reserve((m_size + 1) * 2);
		

	}



	void clear()
	{

	}

	void print()
	{

	}

};

template<typename T>
class TList
{
public:
	TList() = default;
	virtual ~TList()
	{
		clear();
	};

	u32 m_size{ 0 };
	u32 m_capacity{ 0 };

	struct TNode
	{
		T val;
		TNode* next;
	};

	TNode* m_pHead{ nullptr };

	int size() { return m_size; };
	bool isEmpty() { return m_size == 0; };

	T* get(T key)
	{
		auto p = m_pHead;
		while (p)
		{
			if (p->val == key)
				return &(p->val);
			else
				p = p->next;
		}
		return nullptr;
	}

	template<typename Func>
	T* get_if(Func f)
	{
		auto p = m_pHead;
		while (p)
		{
			if (f(p->val))
				return &(p->val);
			else
				p = p->next;
		}
		return nullptr;
	}

	// this function returns returns 0 if found(will not put it as duplicate) and return 1 if insert
	void put(T key)
	{
		m_size++;
		TNode* pNewListItem = new TNode;
		pNewListItem->val = key;

		// so now next of the new is the old new
		pNewListItem->next = m_pHead;
		m_pHead = pNewListItem;
		return;
	}

	int remove(T key) //returns 1 if found, returns 0 if not found
	{
		auto p = m_pHead;
		decltype(p) p2p = nullptr;
		while (p)
		{
			if (p->val == key)
			{
				if (p2p)
					p2p->next = p->next;
				if (p == m_pHead)
					m_pHead = p->next;
				delete p;
				m_size--;
				return 1;
			}
			p2p = p;
			p = p->next;
		}
		// we could not really find it, nothing to remove
		return 0;
	}

	void clear()
	{
		//delete all the automatically allocated list members
		auto p = m_pHead;
		while (p)
		{
			auto tmp = p->next;
			delete p;
			p = tmp;
		}
		m_size = 0;
	}

	void print()
	{
		auto p = m_pHead;
		while (p)
		{
			std::cout << p->val << " ";
			p = p->next;
		}
		std::cout << std::endl;
		return;
	}

	void remove_dups()
	{
		if (!m_pHead || !m_pHead->next)
			return;
		auto p = m_pHead->next; // the first one to be removed
		auto pBefore = m_pHead;
		while (p)
		{
			bool pIsDup = false;
			auto pRunner = m_pHead;
			while (pRunner != p)
			{
				if (pRunner->val == p->val)
				{
					//found duplicate
					pBefore->next = p->next;
					pIsDup = true;
					delete p;
					break;
				}
				pRunner = pRunner->next;
			}

			if (pIsDup)
				p = pBefore->next;
			else
			{
				pBefore = p;
				p = p->next;
			}
		}
	}

	T* nthToLast(u32 n)
	{
		auto p = m_pHead;
		u32 i = 0;
		while (i < n + 1)
		{
			if (!p)
				return nullptr;
			p = p->next;
			i++;
		}
		TNode* pBefore = m_pHead;
		while (p)
		{
			pBefore = pBefore->next;
			p = p->next;
		}
		return &(pBefore->val);
	}
};


#endif /* SEQ_SEARCH_UNORDERED_MAP_H_ */
