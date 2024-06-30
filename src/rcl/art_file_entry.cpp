#include "art_file_entry.h"
#include <format>

using namespace rcl;

art_file_entry::art_file_entry(size_t const _id) : id(_id){};

bool art_file_entry::serialise_in(std::ifstream &ifstream) {
    icicle_check(safe_read_bswap(ifstream, offset));
    icicle_check(safe_read_bswap(ifstream, offset_2));
    icicle_check(safe_read_bswap(ifstream, num_bytes));
    icicle_check(safe_read_bswap(ifstream, num_bytes_2));

    if (num_bytes != num_bytes_2 || offset != offset_2) {
        multi_file = true;
    }

    if (offset != 0) {
        std::cout << to_string() << std::endl;
    }

    return true;
}

bool art_file_entry::serialise_out(std::ofstream &ofstream) {
    write_bswap(ofstream, offset);
    write_bswap(ofstream, offset_2);
    write_bswap(ofstream, num_bytes);
    write_bswap(ofstream, num_bytes_2);

    return true;
}

std::string art_file_entry::to_string() const {
    if (multi_file) {
        return std::format("\t[File {:3}-a] offset:{} size:{:7} bytes [File {:3}-b] offset:{} size:{:7} bytes", id,
                           offset, num_bytes, id, offset_2, num_bytes_2);
    } else {
        return std::format("\t[File {:3}] offset:{} size:{:7} bytes", id, offset, num_bytes);
    }
}
