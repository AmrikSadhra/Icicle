#pragma once

#include "Common/IRawData.h"

namespace RCL {
class DirectoryOffsetTable : private IRawData {
  public:
    DirectoryOffsetTable() = default;
    explicit DirectoryOffsetTable(std::ifstream &ifstream);
    void _SerializeOut(std::ofstream &ofstream) override;

    uint32_t magic_0128;
    uint32_t directory_offsets[73];

  private:
    bool _SerializeIn(std::ifstream &ifstream) override;
};
} // namespace RCL