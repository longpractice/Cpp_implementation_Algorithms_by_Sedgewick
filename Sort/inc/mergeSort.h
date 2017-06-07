/*
 * mergeSort.h
 *
 *  Created on: Dec 12, 2016
 *      Author: Yang
 */

#ifndef MERGESORT_H_
#define MERGESORT_H_

#include <map>
template <class T>
static inline void merge(T* _array, T* _aux, int _lo, int _mi, int _hi)
{
	// this function tries to merge _array[_lo.._mid] to _array[_mid + 1 .. _hi]
	for (int k = _lo; k <= _hi; k++)
		_aux[k] = _array[k]; // first copy into auxillary array

	int i = _lo; int j = _mi + 1;
	for (int k = _lo; k <= _hi; k++)
	{
		if(i > _mi)
			_array[k] = _aux[j++];
		else if (j > _hi)
			_array[k] = _aux[i++];
		else if (_aux[i] < _aux[j])
			_array[k] = _aux[i++];
		else
			_array[k] = _aux[j++];
	}
}

template <class T>
static inline void mergeSort(T* _pVal, int _size)
{
	auto aux = new T[_size];
	for(int sz = 1; sz < _size; sz += sz )
	{
		for(int lo = 0; lo + sz < _size; lo += 2 * sz)
		{
			merge(_pVal, aux, lo, lo + sz - 1, lo + 2*sz - 1 < _size - 1? lo + 2*sz - 1 : _size - 1);
		}
	}

};

#endif /* MERGESORT_H_ */
