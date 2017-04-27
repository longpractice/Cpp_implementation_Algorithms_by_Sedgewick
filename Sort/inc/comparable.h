/*
 * comparable.h
 *
 *  Created on: Dec 11, 2016
 *      Author: Yang
 */

#ifndef COMPARABLE_H_
#define COMPARABLE_H_


template <class T>
void exch(T _array[], int i, int j)
{
	auto tmp = _array[i];
	_array[i] = _array[j];
	_array[j] = tmp;
}

template <class T>
int compare(T a, T b)
{
	if (a > b) return 1;
	else if (a < b) return -1;
	else return 0;
}


template<typename T>
bool verify(T* pArray, int len)
{
	for (int i = 0; i < len - 1; i++)
		if (pArray[i + 1] < pArray[i])
			return false;
	return true;
}


#endif /* COMPARABLE_H_ */
