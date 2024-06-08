#include <iostream>
#include <vector>
#include "RCL/RclFile.h"

int main(int argc, char** argv)
{
	std::vector<std::string> args(argv + 1, argv + argc);
	std::ifstream clarion_rcl(args[0], std::ios::in | std::ios::binary);
	if (!clarion_rcl.is_open())
	{
		return 1;
	}

	uint32_t file_id {0};
	RCL::RclFile rcl_file(clarion_rcl);
	for(auto &file_table : rcl_file.file_tables) {
		for(auto &file : file_table.file_entries) {
			if(file.num_bytes == 0)
				continue;
			std::string file_name = std::to_string(file_id++) + ".png";
			std::ofstream file_out(file_name,  std::ios::out | std::ios::binary);
			file_out.write(file.raw_data.data(), file.raw_data.size());
			file_out.close();
		}
	}

	return 0;
}
