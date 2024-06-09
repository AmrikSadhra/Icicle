#include "ArtFile.h"

using namespace RCL;

ArtFile::ArtFile(std::ifstream &ifstream, uint32_t const _size) : size(_size) {
    ASSERT(this->_SerializeIn(ifstream), "Failed to serialize ArtFile from file stream");
};

void ArtFile::_SerializeOut(std::ofstream &ofstream) {
    ofstream.write(raw_data.data(), size);
}

bool ArtFile::_SerializeIn(std::ifstream &ifstream) {
    raw_data.resize(size);
    SAFE_READ(ifstream, raw_data.data(), size);

    return true;
}
