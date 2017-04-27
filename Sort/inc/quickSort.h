/*
 * quickSort.h
 *
 *  Created on: Dec 30, 2016
 *      Author: Yang
 */

#ifndef QUICKSORT_H_
#define QUICKSORT_H_

#include "comparable.h"
#include "insertionSort.h"
#include <stdlib.h>
template<typename T>
int partition(T* pArray, int lo, int hi)
{
	int parDex = lo + (rand() % (int)(hi - lo + 1)); // find a random number as the partition point
	T parVal = pArray[parDex];
	int left = lo - 1; int right = hi + 1;
	while (true) // do exchanges
	{
		//scan till we find one larger than the partition val, if we reached the end stop the scan
		while (pArray[++left] < parVal)
			if (left >= hi)
				break;
		// scan till we find one smaller than the partition val, if we reached the end stop the scan
		while (pArray[--right] > parVal)
			if (right <= lo)
				break;
		// when we cross (including when left reaches hi and
		if (left >= right)
			break;
		exch(pArray, left, right);
	}
	return right;
};





//three way quick sort which is very efficient
template<typename T>
void threewayQuickSort(T* pArray, int lo, int hi)
{
	if (hi <= lo)
		return;
	if (hi < lo + 15)
	{
		insertionSort(&pArray[lo], hi - lo + 1);
		return;
	}
	int parDex = lo + (rand() % (int)(hi - lo + 1)); // find a random number as the partition point
	T parVal = pArray[parDex];
	int left = lo; int right = hi; int mid = lo;
	while(true)
	{
		int res = compare(pArray[mid], parVal);
		if(res < 0)
			exch(pArray, mid++, left++);
		else if (res > 0)
			exch(pArray, mid, right--);
		else
			mid++;
		if (mid > right)
			break;
	}
	threewayQuickSort(pArray, lo, left - 1);
	threewayQuickSort(pArray, right + 1, hi);
}
template<typename T>
void threewayQuickSort(T* pArray, int size)
{
	threewayQuickSort(pArray, 0, size - 1);
}


template<typename T>
void quickSort(T* pArray, int lo, int hi)
{
	// this will make sure that our recursive call finishes
	if (hi <= lo)
		return;
	if (hi == lo + 1)
		if (pArray[hi] < pArray[lo])
		{
			exch(pArray, hi, lo);
			return;
		}
	int partitionPoint = partition(pArray, lo, hi);
	quickSort(pArray, lo, partitionPoint);
	quickSort(pArray, partitionPoint + 1, hi);
};

template<typename T>
void quickSort(T* pArray, int size)
{
	quickSort(pArray, 0, size - 1);
}




#endif /* QUICKSORT_H_ */
