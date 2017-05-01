/*
 * black_red_tree.h
 *
 *  Created on: Jan 5, 2017
 *      Author: Yang
 */

#ifndef BLACK_RED_TREE_H_
#define BLACK_RED_TREE_H_

template<typename T>
struct TTreeNode
{
	T val{ 0 };
	TTreeNode<T>* pLeft{ nullptr };
	TTreeNode<T>* pRight{ nullptr };
};

template<typename T>
inline bool Is_tree_balanced(const TTreeNode<T>& root)
{
	return maxDepth(&root) - minDepth(&root) <= 1;
}

template<typename T>
inline unsigned int minDepth(const TTreeNode<T>* pRoot)
{
	if (!pRoot)
		return 0;
	unsigned int left_min = minDepth(pRoot->pLeft);
	unsigned int right_min = minDepth(pRoot->pRight);
	return (left_min < right_min ? left_min : right_min) + 1;
}

template<typename T>
inline unsigned int maxDepth(const TTreeNode<T>* pRoot)
{
	if (!pRoot)
		return 0;
	unsigned int left_max = maxDepth(pRoot->pLeft);
	unsigned int right_max = maxDepth(pRoot->pRight);
	return (left_max > right_max ? left_max : right_max) + 1;
}

// for start
template<typename T, unsigned int N>
TTreeNode<T>* array_to_min_height_tree(const T(&data)[N])
{
	return array_to_min_height_tree(data, 0, N - 1);
}

//for recursion
template<typename T, unsigned int N>
TTreeNode<T>* array_to_min_height_tree(const T(&data)[N], int begin, int end)
{
	if (begin > end)
		return nullptr;
	auto pRoot = new TTreeNode<T>;
	int mid = begin + (end - begin) / 2 + (end - begin) % 2;
	pRoot->val = data[mid];
	pRoot->pLeft = array_to_min_height_tree(data, begin, mid - 1);
	pRoot->pRight = array_to_min_height_tree(data, mid + 1, end);
	return pRoot;
}

template<typename T>
inline vector<vector<T>> tree_to_depths_vectors(const TTreeNode<T>* pRoot)
{
	vector<vector<T>> res;
	tree_to_depths_vectors(pRoot, res, 0);
	return res;
}

template<typename T>
inline void tree_to_depths_vectors(const TTreeNode<T>* pRoot, vector<vector<T>>& res, int depth)
{
	if (!(pRoot))
		return;

	if (res.size() <= depth)
		res.resize(depth + 1);

	res[depth].emplace_back(pRoot->val);
	tree_to_depths_vectors(pRoot->pRight, res, depth + 1);
	tree_to_depths_vectors(pRoot->pLeft, res, depth + 1);
}





template<typename T>
inline TTreeNode<T>* find_successor_binary_search_tree
{
}

template<typename TKey, typename TVal>
class TBlack_Red_Tree
{
public:
	explicit TBlack_Red_Tree() {};
	virtual ~TBlack_Red_Tree() {};
	static const bool RED = true;
	static const bool BLACK = false;
	struct TNode
	{
		TNode(const TKey& key, const TVal& val, bool _color)
		{
			size = 1;
			pKey = new TKey;
			*pKey = key;
			pVal = new TVal;
			*pVal = val;
			pLeft = nullptr;
			pRight = nullptr;
			color = _color;
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
		bool color;
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
		if (!isRed(m_pRoot->pLeft))
			m_pRoot->color = RED;
		m_pRoot = delMin(m_pRoot);
		if (m_pRoot)
		m_pRoot->color = BLACK;
	}

	TNode* Min()
	{
		return Min(m_pRoot);
	}

	void del(const TKey& key)
	{
		if (!isRed(m_pRoot->pLeft))
			m_pRoot->color = RED;
		m_pRoot = del(m_pRoot, key);

		if (m_pRoot)
			m_pRoot->color = BLACK;
	}
//private:
	TNode* m_pRoot{ nullptr };
	void cleanNode(TNode* pNode)
	{
		delete pNode->pKey;
		delete pNode->pVal;
		delete pNode;
	}

	TNode* makeNode(const TKey& key, const TVal& val, bool _color)
	{
		return new TNode(key, val, _color);
	}

	int size(TNode* pNode)
	{
		if (pNode)
			return pNode->size;
		else
			return 0;
	}

	TNode* rotateLeft(TNode* pRoot)
	{
		auto sizeRoot = size(pRoot);
		auto pNewRoot = pRoot->pRight; // new root
		pNewRoot->color = pRoot->color;// new root has the same color as the old root
									   //cut off the new root
		pRoot->pRight = pNewRoot->pLeft;
		pRoot->size = size(pRoot->pLeft) + size(pRoot->pRight) + 1;
		pNewRoot->pLeft = pRoot; // left is the old root
		pNewRoot->pLeft->color = RED; // left will be now a red
		pNewRoot->size = sizeRoot;
		return pNewRoot;
	}

	TNode* rotateRight(TNode* pRoot)
	{
		auto sizeRoot = size(pRoot);
		auto pNewRoot = pRoot->pLeft;
		pNewRoot->color = pRoot->color;
		pRoot->pLeft = pNewRoot->pRight;
		pRoot->size = size(pRoot->pLeft) + size(pRoot->pRight) + 1;
		pNewRoot->pRight = pRoot;
		pNewRoot->pRight->color = RED;
		pNewRoot->size = sizeRoot;
		return pNewRoot;
	}

	bool isRed(TNode *pNode)
	{
		if (!pNode)
			return false;
		return pNode->color == RED;
	}

	void flipColor(TNode* pRoot)
	{
		if (pRoot->pLeft)
			pRoot->pLeft->color = !(pRoot->pLeft->color);
		if (pRoot->pRight)
			pRoot->pRight->color = !(pRoot->pRight->color);
		pRoot->color = !(pRoot->color);
	}

	TNode* put(TNode* pRoot, const TKey& key, const TVal& val)
	{
		if (!pRoot) // this is a empty node, put it here
			return makeNode(key, val, RED);
		if (key < *pRoot->pKey)
			pRoot->pLeft = put(pRoot->pLeft, key, val); // put it on the left
		else if (key > *pRoot->pKey)
			pRoot->pRight = put(pRoot->pRight, key, val); // put it on the right sub tree
		else    // replace the current node
			pRoot->set(key, val);
		if (isRed(pRoot->pRight))
			pRoot = rotateLeft(pRoot);
		if (isRed(pRoot->pLeft) && isRed(pRoot->pLeft->pLeft))
			pRoot = rotateRight(pRoot);
		if (isRed(pRoot->pLeft) && isRed(pRoot->pRight))
			flipColor(pRoot);
		// some rotations are needed here
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
		else    // return the current node
			return (pRoot->pVal);
	}

	TNode* m_tmp_min{ nullptr };

	TNode* delMin(TNode* pRoot)
	{
		auto p = delMinNoErase(pRoot);
		if (m_tmp_min) // this is used for temporarily store a min node to avoid it from dangling.
			cleanNode(m_tmp_min);
		return p;
	}

	// this function is able to make the left child red assuming that the current node is red
	// it has two conditions, the first is that the red child is a 2 node and we have to move the parent red down
	// the second condition is that the right child is a 3 node and we move one element from right to left
	TNode* makeLeftRed(TNode* pRoot)
	{
		flipColor(pRoot);
		if (isRed(pRoot->pRight->pLeft)) // we move one from the right to the left
		{
			pRoot->pRight = rotateRight(pRoot->pRight);
			pRoot = rotateLeft(pRoot);
			flipColor(pRoot);
		}
		return pRoot;
	}

	// a symmetric method
	TNode* makeRightRed(TNode* pRoot)
	{
		flipColor(pRoot);

		if (isRed(pRoot->pLeft->pLeft)) // we move one from the right to the left
		{
			pRoot = rotateRight(pRoot);
			flipColor(pRoot);
		}
		return pRoot;
	}

	TNode* repairUp(TNode* pRoot)
	{
		if (isRed(pRoot->pRight))
			pRoot = rotateLeft(pRoot);
		if (isRed(pRoot->pLeft) && isRed(pRoot->pLeft->pLeft))
			pRoot = rotateRight(pRoot);
		if (isRed(pRoot->pLeft) && isRed(pRoot->pRight))
			flipColor(pRoot);
		// some rotations are needed here
		pRoot->size = size(pRoot->pLeft) + size(pRoot->pRight) + 1;
		return pRoot;
	}

	TNode* delMinNoErase(TNode* pRoot)
	{
		if (!pRoot) // this is a empty node, could not find
			return nullptr;
		if (!pRoot->pLeft) // if we do not have a left, we know this is the minimum
		{
			m_tmp_min = pRoot;
			return nullptr;
		}
		if (!isRed(pRoot->pLeft) && !isRed(pRoot->pLeft->pLeft))
			pRoot = makeLeftRed(pRoot);
		pRoot->pLeft = delMinNoErase(pRoot->pLeft);
		pRoot = repairUp(pRoot);
		return pRoot;
	}

	// this should not be used for the root
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
		{
			//We want to delete from the left sub tree, but we have to first make sure that the left
			// sub tree is not a 2 node
			if (!pRoot->pLeft)
				return nullptr;
			if (!isRed(pRoot->pLeft) && !isRed(pRoot->pLeft->pLeft))
				pRoot = makeLeftRed(pRoot);
			pRoot->pLeft = del(pRoot->pLeft, key); // del it on the left
		}
		else // now we either want to delete the current or from the right, no matter which, we have to make sure the right link is a red one
		{
			//We want to delete from the right sub tree, but we have to first make sure that the right
			// sub tree is not a 2 node
			if (isRed(pRoot->pLeft))
				pRoot = rotateRight(pRoot); // force it to be right leaning
										   // if a right leaning black red tree does not have a right node, there must not also be a left node, it must be isolated
			if (*pRoot->pKey == key && !pRoot->pRight)
			{
				cleanNode(pRoot);
				return nullptr;
			}
			if (!isRed(pRoot->pRight) && !isRed(pRoot->pRight->pLeft))
			{

				if (*pRoot->pKey == "Accursed")
					auto volatile some = 1;
				pRoot = makeRightRed(pRoot);

			}
			if (*pRoot->pKey == key)
			{
				auto newRight = delMinNoErase(pRoot->pRight);
				auto newRoot = m_tmp_min;

				//!!!!We should not change the color in this case
				newRoot->color = pRoot->color;
				m_tmp_min = nullptr;
				newRoot->pRight = newRight;
				newRoot->pLeft = pRoot->pLeft; // left is kept
				cleanNode(pRoot);
				pRoot = newRoot;
			}
			else
			{
				pRoot->pRight = del(pRoot->pRight, key); // del it on the right sub tree
			}
		}
		return repairUp(pRoot);
	}
};

#endif /* BLACK_RED_TREE_H_ */
