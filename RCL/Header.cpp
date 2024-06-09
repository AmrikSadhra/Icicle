#include "Header.h"

using namespace RCL;

Header::Header(std::ifstream &ifstream) {
    ASSERT(this->_SerializeIn(ifstream), "Failed to serialize Header from file stream");
};

void Header::_SerializeOut(std::ofstream &ofstream) {
    ASSERT(false, "Header output serialization is not currently implemented");
}

bool Header::_SerializeIn(std::ifstream &ifstream) {
    SAFE_READ(ifstream, &model, sizeof(model));
    SAFE_READ(ifstream, &compile_date, sizeof(compile_date));
    SAFE_READ(ifstream, &oem, sizeof(oem));
    SAFE_READ(ifstream, &unknown, sizeof(unknown));
    SAFE_READ(ifstream, &file_size, sizeof(file_size));
    SAFE_READ(ifstream, &unknown2, sizeof(unknown2));
    SAFE_READ(ifstream, &zeroes, sizeof(zeroes));

    file_size = __builtin_bswap32(file_size);

    SAFE_READ(ifstream, &unknown3, sizeof(unknown3));
    SAFE_READ(ifstream, &directory_offset_table_offsets, sizeof(directory_offset_table_offsets));
    SAFE_READ(ifstream, &unknown4, sizeof(unknown4));

    for (auto &archive_table_offset : directory_offset_table_offsets) {
        archive_table_offset = __builtin_bswap32(archive_table_offset);
    }

    return true;
}
