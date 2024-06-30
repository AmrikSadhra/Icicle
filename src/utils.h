#pragma once

#include <cstdint>
#include <iostream>

#define icicle_assert(condition, message)                                                                              \
    do {                                                                                                               \
        if (!(condition)) {                                                                                            \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ << " line " << __LINE__ << ": "           \
                      << (message);                                                                                    \
            std::exit(1);                                                                                              \
        }                                                                                                              \
    } while (false)

#define icicle_check(condition)                                                                                        \
    if (!(condition)) {                                                                                                \
        std::cerr << "Check `" #condition "` failed in " << __FILE__ << " line " << __LINE__ << std::endl;             \
        return false;                                                                                                  \
    }

namespace utils {
static uint32_t align_to_size(uint32_t const _val, uint32_t const _size) {
    return (_val + _size - 1) / _size * _size;
}
} // namespace utils
