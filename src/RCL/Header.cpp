#include "Header.h"

using namespace RCL;

Header::Header(std::ifstream &ifstream) {
    ASSERT(this->_SerializeIn(ifstream), "Failed to serialize Header from file stream");
};

void Header::_SerializeOut(std::ofstream &ofstream) {
    ASSERT(false, "Header output serialization is not currently implemented");
}

bool Header::_SerializeIn(std::ifstream &ifstream) {
    SAFE_READ(ifstream, &developer, sizeof(developer));
    SAFE_READ(ifstream, &compile_date, sizeof(compile_date));
    SAFE_READ(ifstream, &oem, sizeof(oem));
    SAFE_READ(ifstream, &check1, sizeof(check1));
    SAFE_READ(ifstream, &type, sizeof(type));
    SAFE_READ(ifstream, &check2, sizeof(check2));
    SAFE_READ(ifstream, &file_size, sizeof(file_size));
    SAFE_READ(ifstream, &unknown2, sizeof(unknown2));
    SAFE_READ(ifstream, &zeroes, sizeof(zeroes));

    file_size = __builtin_bswap32(file_size);
    type = __builtin_bswap16(type);
    packing_type = GetType(type);

    SAFE_READ(ifstream, &unknown3, sizeof(unknown3));
    SAFE_READ(ifstream, &directory_offset_table_offsets, sizeof(directory_offset_table_offsets));
    SAFE_READ(ifstream, &unknown4, sizeof(unknown4));

    for (auto &archive_table_offset : directory_offset_table_offsets) {
        archive_table_offset = __builtin_bswap32(archive_table_offset);
    }

    std::cout << ToString() << std::endl;

    return true;
}

Header::Type Header::GetType(uint32_t _type) {
    switch(_type) {
    case 1:
        return Type::FLAT;
    case 4:
        return Type::DIRECTORY;
    default:
        return Type::UNKNOWN;
    }
}

std::string Header::ToString(Header::Type _type) {
    switch(_type) {
    case Header::Type::FLAT:
        return "FLAT";
    case Header::Type::DIRECTORY:
        return "DIRECTORY";
    case Header::Type::UNKNOWN:
        return "UNKNOWN";
    }
    return "ERROR";
}

std::string Header::ToString() {
    return "Developer: " + std::string(developer) + " Compiled: " + std::string(compile_date) + " OEM: " + std::string(oem) + " Type: " + ToString(packing_type);
}

