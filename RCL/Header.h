#pragma once

#include "Common/IRawData.h"

namespace RCL
{
	class Header : private IRawData
	{
	public:
		Header() = default;
		explicit Header(std::ifstream& ifstream);
		void _SerializeOut(std::ofstream& ofstream) override;

		char model[32] {};
		char compile_date[48] {};
		char oem[32] {};
		uint64_t unknown {};
		uint32_t file_size {};
		uint32_t unknown2 {};
		uint8_t zeroes[128] {};
		uint32_t unknown3 {};
		uint32_t archive_table_offsets[4] {};
		uint32_t unknown4 {};

	private:
		bool _SerializeIn(std::ifstream& ifstream) override;
	};
}// namespace RCL
