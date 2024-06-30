#include "rcl_file.h"
#include <format>

using namespace rcl;

bool rcl_file::serialise_in(std::ifstream &ifstream) {
    icicle_check(file_header.serialise_in(ifstream));

    // Check if there's a directory offset table for this RCL type
    use_directory_offset_tables = (file_header.packing_type == packing_type::directory);
    if (use_directory_offset_tables) {
        for (size_t i{0}; i < file_header.directory_offset_table_offsets.size(); ++i) {
            auto &directory_offset_table{directory_offset_tables.emplace_back()};
            icicle_check(directory_offset_table.serialise_in(ifstream));
        }
        uint32_t directory_id{0};
        for (auto &directory_offset_table : directory_offset_tables) {
            for (auto &directory_offset : directory_offset_table.directory_offsets) {
                std::cout << "Reading Directory: " << directory_id++ << std::endl;
                ifstream.seekg(directory_offset, std::ios::beg);
                auto &directory{directories.emplace_back(use_directory_offset_tables)};
                icicle_check(directory.serialise_in(ifstream));
            }
        }
    } else {
        std::cout << "Reading Directory: 1" << std::endl;
        // If no table, construct dummy directories that still read ArtFileEntries
        auto &directory{directories.emplace_back(use_directory_offset_tables)};
        icicle_check(directory.serialise_in(ifstream));
    }

    // Stream pointer end position is well-defined for flat files. For directory type, we end up at offset 0 due to
    // empty art file entries
    uint32_t const aligned_parser_end_position{utils::align_to_size((uint32_t)ifstream.tellg(), sizeof(uint32_t))};
    return use_directory_offset_tables || (aligned_parser_end_position == file_header.file_size);
}

bool rcl_file::serialise_out(std::ofstream &ofstream) {
    icicle_check(file_header.serialise_out(ofstream));
    if (use_directory_offset_tables) {
        for (auto &directory_offset_table : directory_offset_tables) {
            icicle_check(directory_offset_table.serialise_out(ofstream));
        }
    }
    for (auto &directory : directories) {
        icicle_check(directory.serialise_out(ofstream));
    }
    std::cout << "Write end position: " << ofstream.tellp() << " Expected: " << __builtin_bswap32(file_header.file_size)
              << std::endl;
    icicle_check(utils::align_to_size(ofstream.tellp(), sizeof(uint32_t)) == __builtin_bswap32(file_header.file_size));
    return true;
}

size_t rcl_file::dump_art_files(rcl::rcl_file &rcl_file, std::string const &output_dir) {
    size_t num_dumped_files{0};
    for (size_t directory_id{0}; directory_id < rcl_file.directories.size(); ++directory_id) {
        rcl::directory &file_table{rcl_file.directories[directory_id]};
        for (size_t file_id{0}; file_id < file_table.art_files.size(); ++file_id) {
            rcl::art_file &art_file{file_table.art_files[file_id]};
            if (art_file.size == 0)
                continue;
            std::string const art_file_path{std::format("{}/{}_{}.png", output_dir, directory_id, file_id)};
            std::ofstream art_file_out(art_file_path, std::ios::out | std::ios::binary);
            art_file.serialise_out(art_file_out);
            art_file_out.close();
            ++num_dumped_files;
        }
    }
    return num_dumped_files;
}
