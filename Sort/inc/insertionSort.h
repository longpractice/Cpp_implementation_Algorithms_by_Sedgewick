/*
 * insertionSort.h
 *
 *  Created on: Dec 12, 2016
 *      Author: Yang
 */

#ifndef INSERTIONSORT_H_
#define INSERTIONSORT_H_

/*
Insertion sort is kind-of dynamic algorithm, with O(n^2) time, property: 

Online, it can sort a list as it receives it
Stable, keep order if equal
In place, swap is enough

Insertion sort always keep the first k elements sorted. 
The (k+1)th element will be inserted in the first k element at the right position so then k+1 elements will be sorted 
insertion sort is especially good for partially sorted array. It is similar to but better than bubble sort almost in any aspect.
*/
template <typename T>
static inline void insertionSort(T* _pVal, int _size)
{
	for (int iStart = 1; iStart < _size; iStart++)
		// insert the next to the correct position by exchanging to its element before
		for (int i = iStart; i > 0 && _pVal[i-1] > _pVal[i]; i--)
			exch(_pVal, i , i-1);

};


/*
	When swaping is expensive, we should be able to directly insert the (k+1)th element at the correct location
*/
template <typename T>
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
