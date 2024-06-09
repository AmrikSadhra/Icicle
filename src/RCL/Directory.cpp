#include "Directory.h"

using namespace RCL;

Directory::Directory(std::ifstream &ifstream, bool _directory_hierarchy) : directory_hierarchy(_directory_hierarchy) {
    ASSERT(this->_SerializeIn(ifstream), "Failed to serialize Directory from file stream");
};

void Directory::_SerializeOut(std::ofstream &ofstream) {
    ASSERT(false, "Directory output serialization is not currently implemented");
}

bool Directory::_SerializeIn(std::ifstream &ifstream) {
    if(directory_hierarchy) {
        SAFE_READ(ifstream, &size, sizeof(size));
        size = __builtin_bswap32(size);
        num_files = (size - 4) / 16; // ArtFileEntry is 4 * uint32's
    } else {
        // TODO: This is variable. 30 for SPLASH_I. 45 for SPLASH_N. Not encoded in the file, hence we need to be greedy
        // and read entries until we see a PNG header, then backtrack..
        num_files = 30;
    }

    std::cout << "  Contains: " << num_files << " files" << std::endl;

    for (uint32_t file_id{0}; file_id < num_files; ++file_id) {
        art_file_entries.emplace_back(ifstream);
    }

    for (auto &file_entry : art_file_entries) {
        ifstream.seekg(file_entry.offset, std::ios::beg);
        art_files.emplace_back(ifstream, file_entry.num_bytes);
    }

    return true;
}
