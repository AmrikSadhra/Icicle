#pragma once

#include "Common/IRawData.h"
#include "ArchiveTable.h"
#include "FileTable.h"
#include "Header.h"

namespace RCL
{
	class RclFile : private IRawData
	{
	public:
		RclFile() = default;
		explicit RclFile(std::ifstream& ifstream);
		void _SerializeOut(std::ofstream& ofstream) override;

		Header header;
		std::vector<ArchiveTable> archive_tables;
		std::vector<FileTable> file_tables;

	private:
		bool _SerializeIn(std::ifstream& ifstream) override;
	};
}// namespace RCL
