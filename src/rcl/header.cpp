#include "header.h"

using namespace rcl;

bool header::serialise_in(std::ifstream &ifstream) {
    icicle_check(safe_read(ifstream, developer));
    icicle_check(safe_read(ifstream, compile_date));
    icicle_check(safe_read(ifstream, oem));
    icicle_check(safe_read(ifstream, check1));
    icicle_check(safe_read_bswap(ifstream, type));
    icicle_check(safe_read(ifstream, check2));
    icicle_check(safe_read_bswap(ifstream, file_size));
    icicle_check(safe_read(ifstream, unknown2));
    icicle_check(safe_read(ifstream, zeroes));
    icicle_check(safe_read(ifstream, unknown3));
    icicle_check(safe_read_bswap(ifstream, directory_offset_table_offsets));
    icicle_check(safe_read(ifstream, unknown4));

    packing_type = get_packing_type(type);
    icicle_check(packing_type != packing_type::unknown);

    std::cout << to_string() << std::endl;

    return true;
}

bool header::serialise_out(std::ofstream &ofstream) {
    write(ofstream, developer);
    write(ofstream, compile_date);
    write(ofstream, oem);
    write(ofstream, check1);
    write_bswap(ofstream, type);
    write(ofstream, check2);
    write_bswap(ofstream, file_size);
    write(ofstream, unknown2);
    write(ofstream, zeroes);
    write(ofstream, unknown3);
    write_bswap(ofstream, directory_offset_table_offsets);
    write(ofstream, unknown4);

    return true;
}

packing_type header::get_packing_type(uint32_t _type) {
    switch (_type) {
    case 1:
        return rcl::packing_type::flat;
    case 4:
        return rcl::packing_type::directory;
    default:
        return rcl::packing_type::unknown;
    }
}

std::string header::packing_type_to_string(rcl::packing_type _type) {
    switch (_type) {
    case packing_type::flat:
        return "FLAT";
    case packing_type::directory:
        return "DIRECTORY";
    case packing_type::unknown:
        return "UNKNOWN";
    }
    return "ERROR";
}

std::string header::to_string() const {
    return "Developer: " + std::string(developer) + " Compiled: " + std::string(compile_date) +
           " OEM: " + std::string(oem) + " Type: " + packing_type_to_string(packing_type) +
           " Size: " + std::to_string(file_size) + " bytes";
}
