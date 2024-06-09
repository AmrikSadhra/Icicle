#include "File.h"

using namespace RCL;

File::File(std::ifstream &ifstream, uint32_t const _size) : size(_size) {
    ASSERT(this->_SerializeIn(ifstream), "Failed to serialize File from file stream");
};

void File::_SerializeOut(std::ofstream &ofstream) {
    ofstream.write(raw_data.data(), size);
}

bool File::_SerializeIn(std::ifstream &ifstream) {
    raw_data.resize(size);
    SAFE_READ(ifstream, raw_data.data(), size);

    return true;
}
