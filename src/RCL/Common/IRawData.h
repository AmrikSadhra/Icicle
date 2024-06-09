#pragma once

#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

#include "../../Utils.h"

#define SAFE_READ(file, structure, size)                                                                               \
    if ((file).read((char *)(structure), (size)).gcount() != (size))                                                   \
    return false

class IRawData {
  protected:
    virtual bool _SerializeIn(std::ifstream &ifstream) = 0;
    virtual void _SerializeOut(std::ofstream &ofstream) = 0;
};
