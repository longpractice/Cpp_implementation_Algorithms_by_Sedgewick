#pragma once


#include<iterator>

template<typename T>
typename T::iterator upper_bound(
	typename T::iterator begin,
	typename T::iterator end,
	const typename T::value_type &val)
{
	typedef typename T::iterator TIter;
	typedef typename T::value_type TVal;
	typedef typename T::difference_type TDiff;
	TDiff len = std::distance(begin, end);
	TDiff half = 0;
	while (len > 0)
	{
		half = len >> 1;
		auto mid = std::advance(begin, half);
		if (val < *mid)
		{
			len = half;
		}
		else
		{
			len -= half + 1;
			begin = std::advance(mid, 1);
		}
	}
	return begin;
}