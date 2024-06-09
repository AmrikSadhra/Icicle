#pragma once

#include "ArtFile.h"
#include "Common/IRawData.h"

namespace RCL {
class Directory : private IRawData {
  public:
    Directory() = default;
    explicit Directory(std::ifstream &ifstream);
    void _SerializeOut(std::ofstream &ofstream) override;

    struct FileEntry {
        uint32_t offset;
        uint32_t offset_chk;
        uint32_t num_bytes;
        uint32_t num_bytes_chk;
        std::string ToString() {
            return "offset:" + std::to_string(offset) + " offset_chk: " + std::to_string(offset_chk) +
                   " num_bytes:" + std::to_string(num_bytes) + " num_bytes_chk: " + std::to_string(num_bytes_chk);
        }
    };

    // Raw
    uint32_t size{};
    std::vector<FileEntry> file_entries;
    std::vector<ArtFile> files;

    // Derived
    uint32_t num_files{};

  private:
    bool _SerializeIn(std::ifstream &ifstream) override;
};
} // namespace RCL
