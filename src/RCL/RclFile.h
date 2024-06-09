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

    Header header;
    std::vector<DirectoryOffsetTable> directory_offset_tables;
    std::vector<Directory> directories;

  private:
    bool _SerializeIn(std::ifstream &ifstream) override;
};
} // namespace RCL
