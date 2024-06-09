#pragma once

#include "Common/IRawData.h"

namespace RCL {
class ArtFile : private IRawData {
  public:
    ArtFile() = default;
    explicit ArtFile(std::ifstream &ifstream, uint32_t _size);
    void _SerializeOut(std::ofstream &ofstream) override;

    // Derived
    uint32_t size;
    std::vector<char> raw_data;

  private:
    bool _SerializeIn(std::ifstream &ifstream) override;
};
} // namespace RCL
