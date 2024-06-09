#pragma once

#include <iostream>

#define ASSERT(condition, message)                                                                                     \
    do {                                                                                                               \
        if (!(condition)) {                                                                                            \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ << " line " << __LINE__ << ": "           \
                      << message;                                                                                      \
            std::exit(1);                                                                                              \
        }                                                                                                              \
    } while (false)
