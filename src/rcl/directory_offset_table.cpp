#include "directory_offset_table.h"

using namespace rcl;

bool directory_offset_table::serialise_out(std::ofstream &ofstream) {
    write_bswap(ofstream, magic_0128);
    write_bswap(ofstream, directory_offsets);

    return true;
}

bool directory_offset_table::serialise_in(std::ifstream &ifstream) {
    icicle_check(safe_read_bswap(ifstream, magic_0128));
    icicle_check(safe_read_bswap(ifstream, directory_offsets));

    return (magic_0128 == DIR_OFFSET_TABLE_MAGIC);
}
