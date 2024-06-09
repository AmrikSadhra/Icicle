#pragma once

#include "Common/IRawData.h"
#include "Directory.h"
#include "DirectoryOffsetTable.h"
#include "Header.h"

namespace RCL {
class RclFile : private IRawData {
  public:
    RclFile() = default;
    explicit RclFile(std::ifstream &ifstream);
    void _SerializeOut(std::ofstream &ofstream) override;

    struct EndOfDirOffsetTableMarker {
        uint32_t num_padding_bytes;
        std::vector<uint8_t> padding;
    };

    Header header;
    std::vector<DirectoryOffsetTable> directory_offset_tables;
    EndOfDirOffsetTableMarker end_of_dot_marker;
    std::vector<Directory> directories;

  private:
    bool _SerializeIn(std::ifstream &ifstream) override;
};
} // namespace RCL
