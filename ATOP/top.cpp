// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <Sort/inc/insertionSort.h>
#include <type_traits>
#include "YangHelpers.h"
#include "StringHelpers.h"
#include "Stack.h"
#include <Search/inc/seq_search_unordered_map.h>
#include <Graph/Graph.h>

#include <Search/inc/black_red_tree.h>
using namespace std;

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

extern int x;
int main()
{
	int data[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	auto pRoot = array_to_min_height_tree(data);
	
	auto res = tree_to_depths_vectors(pRoot);

	bool isBalanced = Is_tree_balanced(*pRoot);
	//auto min = minDepth(&root);
	while (1);
}

