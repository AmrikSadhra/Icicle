#pragma once

#include <fstream>
#include <iostream>
#include <string.h>

#define SAFE_READ(file, structure, size)                            \
	if ((file).read((char*)(structure), (size)).gcount() != (size)) \
	return false

#define ASSERT(condition, message)                                                                                       \
	do {                                                                                                                 \
		if (!(condition))                                                                                                \
		{                                                                                                                \
			std::cerr << "Assertion `" #condition "` failed in " << __FILE__ << " line " << __LINE__ << ": " << message; \
			std::exit(1);                                                                                                \
		}                                                                                                                \
	} while (false)
