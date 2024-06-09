#pragma once

#include "Common/IRawData.h"

namespace RCL {
class ArtFileEntry : private IRawData {
  public:
    ArtFileEntry() = default;
    explicit ArtFileEntry(std::ifstream &ifstream);
    void _SerializeOut(std::ofstream &ofstream) override;
    std::string ToString();

    uint32_t offset;
    uint32_t offset_chk;
    uint32_t num_bytes;
    uint32_t num_bytes_chk;

  private:
    bool _SerializeIn(std::ifstream &ifstream) override;
};
} // namespace RCL
