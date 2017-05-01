#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "ArrayHelpers.h"
#include "StringHelpers.h"


/*Print multiple value in a single function*/
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






/* Singleton design pattern implemention*/
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











