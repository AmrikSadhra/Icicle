#include "ArchiveTable.h"

using namespace RCL;

ArchiveTable::ArchiveTable(std::ifstream& ifstream)
{
	ASSERT(this->_SerializeIn(ifstream), "Failed to serialize ArchiveTable from file stream");
};

void ArchiveTable::_SerializeOut(std::ofstream& ofstream)
{
	ASSERT(false, "ArchiveTable output serialization is not currently implemented");
}

bool ArchiveTable::_SerializeIn(std::ifstream& ifstream)
{
	SAFE_READ(ifstream, &magic_0128, sizeof(magic_0128));
	SAFE_READ(ifstream, &directory_offsets, sizeof(directory_offsets));

	for(auto &directory_offset : directory_offsets) {
		directory_offset = __builtin_bswap32(directory_offset);
	}

	return true;
}
