#pragma once

#include "common/raw_data_interface.h"
#include "directory.h"
#include "directory_offset_table.h"
#include "header.h"

namespace rcl {
class rcl_file : private raw_data_interface {
  public:
    explicit rcl_file() = default;
    bool serialise_in(std::ifstream &ifstream) override;
    bool serialise_out(std::ofstream &ofstream) override;
    static size_t dump_art_files(rcl::rcl_file &rcl_file, std::string const &output_dir);

    // Raw
    header file_header;
    std::vector<directory_offset_table> directory_offset_tables;
    std::vector<directory> directories;

    // Derived
    bool use_directory_offset_tables{};
};
} // namespace rcl
