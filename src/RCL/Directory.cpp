#include "Directory.h"

using namespace RCL;

Directory::Directory(std::ifstream &ifstream, bool _directory_hierarchy) : directory_hierarchy(_directory_hierarchy) {
    ASSERT(this->_SerializeIn(ifstream), "Failed to serialize Directory from file stream");
};

void Directory::_SerializeOut(std::ofstream &ofstream) {
    ASSERT(false, "Directory output serialization is not currently implemented");
}

bool Directory::_CheckForPNGHeader(std::ifstream &ifstream) {
    uint32_t check {};
    SAFE_READ(ifstream, &check, sizeof(check));
    ifstream.seekg(-sizeof(check), std::ios::cur);
    return check == PNG_HEADER;
}

bool Directory::_SerializeIn(std::ifstream &ifstream) {
    if(directory_hierarchy) {
        SAFE_READ(ifstream, &size, sizeof(size));
        size = __builtin_bswap32(size);
        num_files = (size - 4) / 16; // ArtFileEntry is 4 * uint32's
    } else {
        num_files = 1;
    }

    for (uint32_t file_id{0}; file_id < num_files; ++file_id) {
        art_file_entries.emplace_back(ifstream);

        // If a flat file hierarchy, there is no encoded file count, hence we greedily look for a PNG header
        // to mark the end of the art file entry section
        bool const hit_png {!directory_hierarchy && _CheckForPNGHeader(ifstream)};
        if(hit_png) {
            num_files = file_id + 1;
            break;
        } else {
            ++num_files;
        }
    }

    std::cout << "  Contains: " << num_files << " files" << std::endl;

    for (auto &file_entry : art_file_entries) {
        ifstream.seekg(file_entry.offset, std::ios::beg);
        art_files.emplace_back(ifstream, file_entry.num_bytes);
    }

    return true;
}