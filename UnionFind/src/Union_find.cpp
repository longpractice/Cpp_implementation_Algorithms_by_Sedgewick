//============================================================================
// Name        : Union_find.cpp
// Author      : YangJi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "../inc/weighted_quick_union.h"
#include "../inc/quick_find.h"
#include "../inc/quick_union.h"
#include <windows.h>

int main() {
	auto size = 0;
	std::cin >> size;
	auto tick1 = GetTickCount();
	//TWeightedQuickUnionUF aUnion;
	//TQuickFindUF aUnion;
	TQuickUnionUF aUnion;
	aUnion.Init(size);
	u32 p, q;
	while((std::cin >> p) && (std::cin >> q))
	{
		if(!aUnion.Union(p,q))
			std::cout << p << " " << q << std::endl;
	}
	auto tick2 = GetTickCount();
	std::cout << "Total unions: " << aUnion.Unions_count() << std::endl;
	std::cout << "Ticks used: " << tick2 - tick1 << std::endl;
	return 0;
}
