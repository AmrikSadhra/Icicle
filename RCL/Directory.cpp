#include "Directory.h"

using namespace RCL;

Directory::Directory(std::ifstream &ifstream) {
    ASSERT(this->_SerializeIn(ifstream), "Failed to serialize Directory from file stream");
};

void Directory::_SerializeOut(std::ofstream &ofstream) {
    ASSERT(false, "Directory output serialization is not currently implemented");
}

bool Directory::_SerializeIn(std::ifstream &ifstream) {
    SAFE_READ(ifstream, &size, sizeof(size));
    size = __builtin_bswap32(size);

    num_files = (size - 4) / sizeof(FileEntry);
    std::cout << "Contains: " << num_files++ << " files" << std::endl;

    for (uint32_t file_id{0}; file_id < num_files; ++file_id) {
        auto &file_entry{file_entries.emplace_back()};
        ifstream.read((char *)&file_entry, sizeof(FileEntry));

        file_entry.num_bytes = __builtin_bswap32(file_entry.num_bytes);
        file_entry.num_bytes_chk = __builtin_bswap32(file_entry.num_bytes_chk);
        file_entry.offset = __builtin_bswap32(file_entry.offset);
        file_entry.offset_chk = __builtin_bswap32(file_entry.offset_chk);

        if (file_entry.num_bytes != file_entry.num_bytes_chk || file_entry.offset != file_entry.offset_chk) {
            std::cout << "Warning; File ID " << file_id << " has mismatched attributes:" << file_entry.ToString()
                      << std::endl;
        }
    }

    for (auto &file_entry : file_entries) {
        ifstream.seekg(file_entry.offset, std::ios::beg);
        files.emplace_back(ifstream, file_entry.num_bytes);
    }

    return true;
}
