#pragma once

#include <string>
#include "int_types_with_width.h"

/*reverse a c string*/
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

/* replace a certain char in a string by another string*/
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

/*remove duplicate chars in a string*/
static inline int remove_duplications(std::string& str)
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
	return str.length();
}
inline int dummy()
{
	return 1;
}