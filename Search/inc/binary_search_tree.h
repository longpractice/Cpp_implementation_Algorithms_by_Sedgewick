/*
 * Binary_Search_Tree.h
 *
 *  Created on: Jan 3, 2017
 *      Author: Yang
 */

#ifndef BINARY_SEARCH_TREE_H_
#define BINARY_SEARCH_TREE_H_

template<typename TKey, typename TVal>
class TBinary_Search_Tree{
public:
	explicit TBinary_Search_Tree() {};
	virtual ~TBinary_Search_Tree() {};
	struct TNode
	{
		TNode(const TKey& key, const TVal& val)
		{
			size = 1;
			pKey = new TKey;
			*pKey = key;
			pVal = new TVal;
			*pVal = val;
			pLeft = nullptr;
			pRight = nullptr;
		};
		void set(const TKey& key, const TVal& val)
		{
			*pKey = key;
			*pVal = val;
		}
		int size;
		TKey* pKey;
		TVal* pVal;
		TNode* pLeft;
		TNode* pRight;
	};

	int size()
	{
		return size(m_pRoot);
	}

	void put(const TKey& key, const TVal& val)
	{
		m_pRoot = put(m_pRoot, key, val);
	}

	TVal* find(const TKey& key)
	{
		return find(m_pRoot, key);
	}

	void delMin()
	{
		m_pRoot = delMin(m_pRoot);
	}

	TNode* Min()
	{
		return Min(m_pRoot);
	}

	void del(const TKey& key)
	{
		m_pRoot = del(m_pRoot, key);
	}

private:

	TNode* m_pRoot{ nullptr };

	void cleanNode(TNode* pNode)
	{
		delete pNode->pKey;
		delete pNode->pVal;
		delete pNode;
	}
	TNode* makeNode(const TKey& key, const TVal& val)
	{
		return new TNode(key, val);
	}

	int size(TNode* pNode)
	{
		if (pNode)
			return pNode->size;
		else
			return 0;
	}

	TNode* put(TNode* pRoot, const TKey& key, const TVal& val)
	{
		if (!pRoot) // this is a empty node, put it here
			return makeNode(key, val);
		else
		{
			if (key < *pRoot->pKey)
				pRoot->pLeft = put(pRoot->pLeft, key, val); // put it on the left
			else if (key > *pRoot->pKey)
				pRoot->pRight = put(pRoot->pRight, key, val); // put it on the right sub tree
			else	// replace the current node
				pRoot->set(key, val);
		}
		pRoot->size = size(pRoot->pLeft) + size(pRoot->pRight) + 1;
		return pRoot;
	}

	TVal* find(TNode* pRoot, const TKey& key)
	{
		if (!pRoot) // this is a empty node, could not find
			return nullptr;
		if (key < *pRoot->pKey)
			return find(pRoot->pLeft, key); // find it on the left
		else if (key > *pRoot->pKey)
			return find(pRoot->pRight, key); // find it on the right sub tree
		else	// return the current node
			return (pRoot->pVal);
	}

	TNode* delMin(TNode* pRoot)
	{
		if (!pRoot) // this is a empty node, could not find
			return nullptr;

		// try to del left
		if (pRoot->pLeft)
			pRoot->pLeft = delMin(pRoot->pLeft);
		else //it does not have a left, it will have to del itself
		{
			auto tmp = pRoot->pRight;
			cleanNode(pRoot);
			return tmp;
		}
		pRoot->size = size(pRoot->pLeft) + size(pRoot->pRight) + 1;
		return pRoot;
	}

	TNode* delMinNoErase(TNode* pRoot)
	{
		if (!pRoot) // this is a empty node, could not find
			return nullptr;

		// try to del left
		if (pRoot->pLeft)
			pRoot->pLeft = delMin(pRoot->pLeft);
		else //it does not have a left, it will have to del itself
		{
			return pRoot->pRight;
		}
		pRoot->size = size(pRoot->pLeft) + size(pRoot->pRight) + 1;
		return pRoot;
	}

	TNode* Min(TNode* pRoot)
	{
		if (!pRoot) // this is a empty node, could not find
			return nullptr;

		if (pRoot->pLeft)// try to find left
			return Min(pRoot->pLeft);
		else //it does not have a left
			return pRoot;
	}

	TNode* del(TNode* pRoot, const TKey& key)
	{
		if (!pRoot) // this is a empty node, could not find
			return nullptr;

		if (key < *pRoot->pKey)
			pRoot->pLeft = del(pRoot->pLeft, key); // del it on the left
		else if (key > *pRoot->pKey)
			pRoot->pRight = del(pRoot->pRight, key); // del it on the right sub tree
		else	// del the current node
		{
			if (!pRoot->pLeft)// if the left is empty, we have to put right up
			{

				auto tmp = pRoot->pRight;
				cleanNode(pRoot); //delete current node
				return tmp;
			}
			if (!pRoot->pRight)// if the left is empty, we have to put right up
			{
				auto tmp = pRoot->pLeft;
				cleanNode(pRoot); //delete current node
				return tmp;
			}

			// in this condition, our to-be-deleted has two children, we have to put the successer(min of right sub tree) here, and put right-sub-tree-after-min-del on the right
			auto newRoot = Min(pRoot->pRight);
			newRoot->pRight = delMinNoErase(pRoot->pRight);
			newRoot->pLeft = pRoot->pLeft; // left is kept
			cleanNode(pRoot);
			pRoot = newRoot;
		}
		pRoot->size = size(pRoot->pLeft) + size(pRoot->pRight) + 1;
		return pRoot;
	}
};



#endif /* BINARY_SEARCH_TREE_H_ */
