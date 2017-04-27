#ifndef SELECTIONSORT_H_
#define SELECTIONSORT_H_

#include "comparable.h"

//selection sort has a lot of compares but has the minimum number of exchanges
template <class T>
static inline void selectionSort(T* _pVal, int _size)
{
	for (int iStart = 0; iStart < _size; iStart++)
		//find the minimum from iStart to end
		for (int i = iStart + 1; i < _size; i++)
			if (_pVal[i] < _pVal[iStart])
				exch(_pVal, i , iStart);
};




#endif
