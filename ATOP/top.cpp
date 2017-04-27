// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Sort/inc/insertionSort.h>
#include <type_traits>
#include "YangHelpers.h"
#include <Search/inc/seq_search_unordered_map.h>

using namespace std;
int main()
{
	TList<u32> bag;
	bag.put(1);
	bag.put(2);
	bag.put(3);
	bag.put(4);
	//bag.remove_dups();
	auto p = bag.nthToLast(1);
	if (p)
		cout << *p << std::endl;
	else
		cout << "nullptr" << endl;
	//bag.print();

	while (1);
}

