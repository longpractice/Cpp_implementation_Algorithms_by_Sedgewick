#pragma once

#include <iostream>
#include <vector>
#include <string>

#define u32 unsigned int

template<typename T> static inline void print_multiple(std::ostream &os, const T& firstArg)
{
	os << firstArg << std::endl;
}

template<typename T, typename ...Args> static inline void print_multiple(std::ostream &os, const T& firstArg, const Args& ...args)
{
	//std::cout << sizeof... (args) << std::endl;
	unsigned int size = sizeof... (args);
	if (size == 0)
		os << firstArg << std::endl;
	else
	{
		os << firstArg << std::endl;
		print(os, args...);
	}
}

//reverse a string
static inline void reverse_str(char* pStart)
{
	if (!*pStart)
		return;

	//first find out the end of the string
	auto pEnd = pStart;
	while (*pEnd)
		pEnd++;
	pEnd--;
	while (pStart < pEnd)
	{
		char tmp = *pStart;
		*pStart++ = *pEnd;
		*pEnd-- = tmp;
	}
}

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

static void replace_char_by_str(std::string& target, char from, std::string to)
{
	u32 oldTargetLen = target.length();
	u32 targetLen = oldTargetLen; //expand or shrink

	u32 toLen = to.length(); //unit after len
	u32 fromLen = sizeof(from); //unit before len

	int unitDiff = toLen - fromLen; //unit len diff

	bool found = false;
	for (auto ch : target)
		if (ch == from)
		{
			targetLen += unitDiff;
			found = true;
		}

	if (!found)
		return;



	if (targetLen > oldTargetLen) // we need to expand the string first
	{
		target.resize(targetLen);
		//put the string from the back to front
		u32 iDest = targetLen;
		for (u32 iSrc = oldTargetLen - 1; iSrc != 0; iSrc--)
		{
			bool isMatch = target[iSrc] == from;
			auto cpyLen = isMatch ? toLen : fromLen;
			auto pSrc = isMatch ? &to[0] : &target[iSrc];
			iDest -= cpyLen;
			auto pDest = &target[iDest];
			memcpy(pDest, pSrc, cpyLen);
		}
	}
	else// we may have to shrink the string last
	{
		//put the string from front to end
		u32 iDest = 0;
		for (u32 iSrc = 0; iSrc < oldTargetLen; iSrc++)
		{
			bool isMatch = target[iSrc] == from;
			auto cpyLen = isMatch ? toLen : fromLen;
			auto pSrc = isMatch ? &to[0] : &target[iSrc];
			auto pDest = &target[iDest];
			memcpy(pDest, pSrc, cpyLen);
			iDest += cpyLen;
		}
		target.resize(targetLen);
	}

}


//singleton 

class TSingleton
{
public: 
	TSingleton(const TSingleton&) = delete; //no copy construction allowed
	TSingleton& operator=(const TSingleton&) = delete;
	static TSingleton& getInstance()
	{
		static TSingleton instance;
		return instance;
	}
private:
	TSingleton() = default;
};

static inline void remove_duplications(std::string& str)
{
	auto len = str.length();
	u32 tail = 0;
	for (u32 i = 0; i < len; i++)
	{
		u32 j = 0;
		for (j = 0; j < tail; j++)
			if (str[j] == str[i])
				break;
		if (j == tail)
			str[tail++] = str[i];
	}
	str.resize(tail);
}


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


template<typename T, unsigned int N>
static inline void rotate_90(T (&data)[N][N])
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
}
