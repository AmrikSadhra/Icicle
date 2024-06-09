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

    //Check if there's a directory offset table for this RCL type
    bool const use_directory_offset_tables{header.packing_type == Header::Type::DIRECTORY};
    if(use_directory_offset_tables) {
        for (auto &directory_offset_table_offset : header.directory_offset_table_offsets) {
            directory_offset_tables.emplace_back(ifstream);
        }
        uint32_t directory_id{0};
        for (auto &directory_offset_table : directory_offset_tables) {
            for (auto &directory_offset : directory_offset_table.directory_offsets) {
                std::cout << "Reading Directory: " << directory_id++ << std::endl;
                ifstream.seekg(directory_offset, std::ios::beg);
                directories.emplace_back(ifstream, use_directory_offset_tables);
            }
        }
    } else {
        // If no table, construct dummy directories that still read ArtFileEntries
        directories.emplace_back(ifstream, use_directory_offset_tables);
    }

    return true;
}
