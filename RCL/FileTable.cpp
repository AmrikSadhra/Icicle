#include "FileTable.h"

using namespace RCL;

FileTable::FileTable(std::ifstream& ifstream)
{
	ASSERT(this->_SerializeIn(ifstream), "Failed to serialize FileTable from file stream");
};

void FileTable::_SerializeOut(std::ofstream& ofstream)
{
	ASSERT(false, "FileTable output serialization is not currently implemented");
}

bool FileTable::_SerializeIn(std::ifstream& ifstream)
{
	SAFE_READ(ifstream, &size, sizeof(size));
	size = __builtin_bswap32(size);

	// TODO: Separate this into own class
	num_files = (size-4)/sizeof(FileEntry);

	for(uint32_t file_id {0}; file_id < num_files; ++file_id) {
		auto &file_entry {file_entries.emplace_back()};
		ifstream.read((char*)&file_entry, 16);

		file_entry.num_bytes = __builtin_bswap32(file_entry.num_bytes);
		file_entry.num_bytes_chk = __builtin_bswap32(file_entry.num_bytes_chk);
		file_entry.offset = __builtin_bswap32(file_entry.offset);
		file_entry.offset_chk = __builtin_bswap32(file_entry.offset_chk);

		if (file_entry.num_bytes != file_entry.num_bytes_chk || file_entry.offset != file_entry.offset_chk) {
			std::cout << "Warning; File ID " << file_id << " has mismatched attributes:" << file_entry.ToString() << std::endl;
		}
	}

	for (auto &file : file_entries) {
		ifstream.seekg(file.offset, std::ios::beg);
		file.raw_data.resize(file.num_bytes);
		SAFE_READ(ifstream, file.raw_data.data(), file.num_bytes);
	}

	return true;
}
