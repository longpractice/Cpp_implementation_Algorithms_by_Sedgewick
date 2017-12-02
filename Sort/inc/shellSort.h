/*
 * shellSort.h
 *
 *  Created on: Dec 12, 2016
 *      Author: Yang
 */

#ifndef SHELLSORT_H_
#define SHELLSORT_H_

//shell sort is faster than insertion sort because it exchanges elements which are further away
//note that if a sequence is g sorted and if you later do a h sort, it remains g sorted(the proof is subtle and not easy)
template <class T>
static inline void shellSort(T* _pVal, int _size)
{
	int h = 1;
	while(h < _size/3)
		h = 3*h + 1;
	while(h >= 1)
	{
		for (int iStart = h; iStart < _size; iStart++)
			// insert the next to the correct position by exchanging to its element before
			for (int i = iStart; i >= h && _pVal[i-h] > _pVal[i]; i -= h)
				exch(_pVal, i , i-h);
		h /= 3;
	}
};



#endif /* SHELLSORT_H_ */
