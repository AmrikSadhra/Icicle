#include "RclFile.h"

using namespace RCL;

RclFile::RclFile(std::ifstream &ifstream) {
    ASSERT(this->_SerializeIn(ifstream), "Failed to serialize RclFile from file stream");
};

void RclFile::_SerializeOut(std::ofstream &ofstream) {
    ASSERT(false, "RclFile output serialization is not currently implemented");
}

bool RclFile::_SerializeIn(std::ifstream &ifstream) {
    header = Header(ifstream);

    for (auto &directory_offset_table_offset : header.directory_offset_table_offsets) {
        directory_offset_tables.emplace_back(ifstream);
    }
    SAFE_READ(ifstream, &end_of_dot_marker.num_padding_bytes, sizeof(end_of_dot_marker.num_padding_bytes));
    end_of_dot_marker.num_padding_bytes = __builtin_bswap32(end_of_dot_marker.num_padding_bytes);
    end_of_dot_marker.padding.resize(end_of_dot_marker.num_padding_bytes);
    SAFE_READ(ifstream, &end_of_dot_marker.padding, end_of_dot_marker.padding.size());

    uint32_t directory_id{0};
    for (auto &archive_table : directory_offset_tables) {
        for (auto &directory_offset : archive_table.directory_offsets) {
            std::cout << "Reading Directory: " << directory_id++ << std::endl;
            ifstream.seekg(directory_offset, std::ios::beg);
            directories.emplace_back(ifstream);
        }
    }

    return true;
}
