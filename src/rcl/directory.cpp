#include "directory.h"

using namespace rcl;

directory::directory(bool const _directory_hierarchy) : directory_hierarchy(_directory_hierarchy) {
}

bool directory::_check_for_png_header(std::ifstream &ifstream) {
    uint32_t check{};
    icicle_check(safe_read(ifstream, check));
    ifstream.seekg((std::streamoff) - sizeof(check), std::ios::cur);
    return check == PNG_HEADER;
}

bool directory::serialise_in(std::ifstream &ifstream) {
    if (directory_hierarchy) {
        icicle_check(safe_read_bswap(ifstream, size));
        num_files = (size - 4) / 16; // ArtFileEntry is 4 * uint32's
    } else {
        num_files = 1;
    }

    for (uint32_t file_id{0}; file_id < num_files; ++file_id) {
        auto &art_file_entry{art_file_entries.emplace_back(file_id)};
        icicle_check(art_file_entry.serialise_in(ifstream));

        // If a flat file hierarchy, there is no encoded file count, hence we greedily look for a PNG header
        // to mark the end of the art file entry section
        if (!directory_hierarchy) {
            bool const hit_png{_check_for_png_header(ifstream)};
            if (hit_png) {
                num_files = file_id + 1;
                break;
            } else {
                ++num_files;
            }
        }
    }

    std::cout << to_string() << std::endl;

    // Seek and dump the files using entry offset data
    for (auto &art_file_entry : art_file_entries) {
        if (art_file_entry.num_bytes == 0)
            continue;
        // File A
        ifstream.seekg(art_file_entry.offset, std::ios::beg);
        auto &art_file_a{art_files.emplace_back(art_file_entry, art_file_entry.num_bytes, false)};
        icicle_check(art_file_a.serialise_in(ifstream));
        // File B
        if (art_file_entry.multi_file) {
            ifstream.seekg(art_file_entry.offset_2, std::ios::beg);
            auto &art_file_b{art_files.emplace_back(art_file_entry, art_file_entry.num_bytes_2, true)};
            icicle_check(art_file_b.serialise_in(ifstream));
        }
    }

    return true;
}

bool directory::serialise_out(std::ofstream &ofstream) {
    if (directory_hierarchy) {
        write_bswap(ofstream, size);
    }
    // TODO: Rewrite the offsets and sizes dependent upon Art Files
    for (auto &art_file_entry : art_file_entries) {
        icicle_check(art_file_entry.serialise_out(ofstream));
    }
    for (auto &art_file : art_files) {
        uint32_t const offset{
            __builtin_bswap32(art_file.is_file_b ? art_file.parent.offset_2 : art_file.parent.offset)};
        ofstream.seekp(offset, std::ios::beg);
        icicle_check(art_file.serialise_out(ofstream));
    }
    return true;
}

std::string directory::to_string() const {
    return "  Contains: " + std::to_string(num_files) + " entries";
}