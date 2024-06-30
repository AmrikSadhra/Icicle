#include "art_file.h"

using namespace rcl;

art_file::art_file(art_file_entry &_parent, uint32_t const _size, bool const _is_file_b)
    : parent(_parent), size(_size), is_file_b{_is_file_b} {};

bool art_file::serialise_in(std::ifstream &ifstream) {
    raw_data.resize(size);
    icicle_check(ifstream.read((char *)raw_data.data(), size).gcount() == size);

    return true;
}

bool art_file::serialise_out(std::ofstream &ofstream) {
    ofstream.write(raw_data.data(), size);
    return true;
}
