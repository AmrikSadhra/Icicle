#include "RclFile.h"

using namespace RCL;

RclFile::RclFile(std::ifstream& ifstream)
{
	ASSERT(this->_SerializeIn(ifstream), "Failed to serialize RclFile from file stream");
};

void RclFile::_SerializeOut(std::ofstream& ofstream)
{
	ASSERT(false, "RclFile output serialization is not currently implemented");
}

bool RclFile::_SerializeIn(std::ifstream& ifstream)
{
	header = Header(ifstream);
	for (auto &archive_table_offset : header.archive_table_offsets) {
		archive_tables.emplace_back(ifstream);
	}
	uint32_t file_table_id {0};
	for(auto &archive_table : archive_tables) {
		for (auto &directory_offset : archive_table.directory_offsets) {
			ifstream.seekg(directory_offset, std::ios::beg);
			file_tables.emplace_back(ifstream);
			std::cout << "File Table " << std::to_string(file_table_id++) << std::endl;
		}
	}

	return true;
}
