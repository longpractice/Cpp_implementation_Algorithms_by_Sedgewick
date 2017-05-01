#pragma once
#include"int_types_with_width.h"
#include "StringHelpers.h"
/*
* rotate an array with dimension N*N,
* this is done basically in place, so it does not require much more space
*/

template<typename T, unsigned int N>
static inline void rotate_90(T(&data)[N][N])
{
	unsigned int half = N / 2 + (N % 2);
	unsigned int subHalf = N / 2;
	for (u32 i = 0; i < half; i++)
	{
		for (u32 j = 0; j < subHalf; j++)
		{
			T tmp = data[i][j];
			data[i][j] = data[N - 1 - j][i];
			data[N - 1 - j][i] = data[N - 1 - i][N - 1 - j];
			data[N - 1 - i][N - 1 - j] = data[j][N - 1 - i];
			data[j][N - 1 - i] = tmp;
		}
	}
}

/* Mark the including row and colume zero, if a certain element is zero */
template<typename T, u32 M, u32 N>
static inline void markZeros(T(&a)[M][N])
{
	u32 zeroRows[M]{};
	u32 zeroCols[N]{};
	for (u32 i = 0; i < M; i++)
	{
		for (u32 j = 0; j < N; j++)
		{
			if (a[i][j] == 0)
			{
				zeroRows[i] = 1;
				zeroCols[j] = 1;
			}
		}
	}

	for (u32 i = 0; i < M; i++)
	{
		for (u32 j = 0; j < N; j++)
		{
			if (zeroRows[i] || zeroCols[j])
			{
				a[i][j] = 0;
			}
		}
	}
};

/*Get a container's size
no matter if array or stl container*/
template<typename T, unsigned int N>
static inline constexpr unsigned int container_size(T(&)[N]) noexcept
{
	return N;
}

template<typename T>
static inline unsigned int container_size(T &_data) noexcept
{
	return _data.size();
}



/* remove duplicates inside a container, return the end iterator after removing */
template<typename TIter>
static inline TIter remove_duplicates(TIter begin, TIter end)
{
	TIter tail = begin;
	for (TIter iExam = begin; iExam < end; iExam++)
	{
		TIter jPushed = begin;
		for (; jPushed < tail; jPushed++)
			if (*jPushed == *iExam)
				break;
		if (jPushed == tail)
			*tail++ = *iExam;
	}
	return tail;
};