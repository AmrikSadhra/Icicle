#pragma once

#include "ArtFile.h"
#include "ArtFileEntry.h"
#include "Common/IRawData.h"

namespace RCL {
class Directory : private IRawData {
  public:
    Directory() = default;
    explicit Directory(std::ifstream &ifstream);
    void _SerializeOut(std::ofstream &ofstream) override;

    // Raw
    uint32_t size{};
    std::vector<ArtFileEntry> art_file_entries;
    std::vector<ArtFile> art_files;

    // Derived
    uint32_t num_files{};

  private:
    bool _SerializeIn(std::ifstream &ifstream) override;
};
} // namespace RCL
