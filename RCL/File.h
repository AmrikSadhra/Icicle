#pragma once

#include "Common/IRawData.h"

namespace RCL
{
	class File : private IRawData
	{
	public:
		File() = default;
		explicit File(std::ifstream& ifstream);
		void _SerializeOut(std::ofstream& ofstream) override;

		std::vector<uint8_t> raw_data;

	private:
		bool _SerializeIn(std::ifstream& ifstream) override;
	};
}// namespace RCL
