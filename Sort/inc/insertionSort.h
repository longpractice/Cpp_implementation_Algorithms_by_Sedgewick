/*
 * insertionSort.h
 *
 *  Created on: Dec 12, 2016
 *      Author: Yang
 */

#ifndef INSERTIONSORT_H_
#define INSERTIONSORT_H_

//insertion sort is especially good for partially sorted array
template <class T>
static inline void insertionSort(T* _pVal, int _size)
{
	for (int iStart = 1; iStart < _size; iStart++)
		// insert the next to the correct position by exchanging to its element before
		for (int i = iStart; i > 0 && _pVal[i-1] > _pVal[i]; i--)
			exch(_pVal, i , i-1);

};

template <class T>
static inline void insertionSortEfficient(T* _pVal, int _size)
{
	// this method is more efficient because it directly exchange with the one which should be promoted.
	for (int iStart = 1; iStart < _size; iStart++)
	{
		auto tmp = _pVal[iStart];
		int i = 0;
		for (i = iStart - 1; i >= 0 && _pVal[i] > tmp; i--)
			_pVal[i + 1] = _pVal[i];
		_pVal[i + 1] = tmp;
	}
};
#endif /* INSERTIONSORT_H_ */
