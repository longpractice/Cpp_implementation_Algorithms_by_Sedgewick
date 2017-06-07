// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include<vector>
#include <iostream>
int cnt = 0;
struct intx
{
	intx() {};
	intx(int i) : m(i) {};
	int m;
	bool operator<(const intx &b) const
	{
		++cnt;
		if (m < b.m)
			return true;
		else
			return false;
	}
};




template<typename T>
int find_in_vector(const std::vector<T> &vec, const T &val)
{
	if (vec.size() == 0) //cannot find in an empty vector
		return -1;

	int size = vec.size();
	int len = size; //length of the range
	int half = 0; //half of the length
	int begin = 0; // begin of the range
	while (len > 0)
	{
		half = len >> 1; //binary search
		if(vec[begin + half] < val) //must be in the right half(excluding half)
		{
			len -= half + 1;
			begin += half + 1;
		}
		else // in the left half, but the middle could be picked later
			len = half;
	}

	//we have found a lower bound, now compare it with the value
	if (begin == size || val < vec[begin])
		return -1;

	return begin;
}

int main()
{
	std::vector<intx> vec(200000, 0);
	for (int i = 0; i < 200000; i++)
	{
		vec[i] = intx{ i };
	}
	auto res = find_in_vector(vec, intx{ 190000 });
	std::cout << res << " " << cnt << std::endl;

	while (1)
		continue;
}