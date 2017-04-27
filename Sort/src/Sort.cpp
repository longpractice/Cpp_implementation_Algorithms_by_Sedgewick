//============================================================================
// Name        : Sort.cpp
// Author      : YangJi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include "../inc/selectionSort.h"
#include "../inc/insertionSort.h"
#include "../inc/mergeSort.h"
#include "../inc/quickSort.h"
#include "../inc/shellSort.h"
#include "../inc/priorityQueue.h"
#include <stdlib.h>
#include <windows.h>


using namespace std;

int main() {
	std::cout << "Hello World." << std::endl;
	int toBeSorted[100000];
	int size = sizeof(toBeSorted)/sizeof(toBeSorted[0]);
	for (int i = 0; i < size; i++)
		toBeSorted[i] = rand();

//	auto t1 = GetTickCount();
//	threewayQuickSort(toBeSorted, size);
//	auto volatile tDiff = GetTickCount() - t1;
//
//	bool correct = verify(toBeSorted, size);
	//0.015s for mergeSort = quicksort. 6s for efficient insertion sort. 0.046s for shell sort. 18 for insertion sort. 29 for selection sort.


	auto pq = TPriorityQueue<int>(100000);
	int items[5] = {3, 6 ,1, 9, 8};
	for(auto i : toBeSorted)
		pq.insert(i);

	for(auto i : toBeSorted)
		cout << pq.delMax() << " " << endl;
	pq.printMe();
	while(1);
	//cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
