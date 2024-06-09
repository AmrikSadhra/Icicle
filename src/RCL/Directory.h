#pragma once

#include "ArtFile.h"
#include "ArtFileEntry.h"
#include "Common/IRawData.h"

namespace RCL {
class Directory : private IRawData {
  public:
    Directory() = default;
    explicit Directory(std::ifstream &ifstream, bool _directory_hierarchy);
    void _SerializeOut(std::ofstream &ofstream) override;

    // Raw
    uint32_t size{};
    std::vector<ArtFileEntry> art_file_entries;
    std::vector<ArtFile> art_files;

    // Derived
    bool directory_hierarchy;
    uint32_t num_files{};

  private:
    bool _SerializeIn(std::ifstream &ifstream) override;
    bool _CheckForPNGHeader(std::ifstream &ifstream);

    uint32_t const PNG_HEADER = 0x474E5089;
};
} // namespace RCL
