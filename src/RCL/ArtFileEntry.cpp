#include "ArtFileEntry.h"

using namespace RCL;

ArtFileEntry::ArtFileEntry(std::ifstream &ifstream) {
    ASSERT(this->_SerializeIn(ifstream), "Failed to serialize ArtFileEntry from file stream");
};

void ArtFileEntry::_SerializeOut(std::ofstream &ofstream) {
    ASSERT(false, "ArtFileEntry output serialization is not currently implemented");
}

bool ArtFileEntry::_SerializeIn(std::ifstream &ifstream) {
    SAFE_READ(ifstream, &num_bytes, sizeof(num_bytes));
    SAFE_READ(ifstream, &num_bytes_chk, sizeof(num_bytes_chk));
    SAFE_READ(ifstream, &offset, sizeof(offset));
    SAFE_READ(ifstream, &offset_chk, sizeof(offset_chk));

    num_bytes = __builtin_bswap32(num_bytes);
    num_bytes_chk = __builtin_bswap32(num_bytes_chk);
    offset = __builtin_bswap32(offset);
    offset_chk = __builtin_bswap32(offset_chk);

    if (num_bytes != num_bytes_chk || offset != offset_chk) {
        std::cerr << "Warning; File has mismatched attributes:" << ToString() << std::endl;
    }
    return true;
}

std::string ArtFileEntry::ToString() {
    return "offset:" + std::to_string(offset) + " offset_chk: " + std::to_string(offset_chk) +
           " num_bytes:" + std::to_string(num_bytes) + " num_bytes_chk: " + std::to_string(num_bytes_chk);
}
