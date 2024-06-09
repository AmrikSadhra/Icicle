#include <iostream>
#include <vector>

#include "RCL/RclFile.h"

int main(int argc, char **argv) {
    std::vector<std::string> args(argv + 1, argv + argc);
    std::ifstream clarion_rcl(args[0], std::ios::in | std::ios::binary);
    if (!clarion_rcl.is_open()) {
        return 1;
    }

    RCL::RclFile rcl_file(clarion_rcl);
    for (uint32_t directory_id{0}; directory_id < rcl_file.directories.size(); ++directory_id) {
        RCL::Directory &file_table{rcl_file.directories[directory_id]};
        for (uint32_t file_id{0}; file_id < file_table.num_files; ++file_id) {
            RCL::File &file{file_table.files[file_id]};
            if (file.size == 0)
                continue;
            std::string file_name {std::to_string(directory_id) + "_" + std::to_string(file_id) + ".png"};
            std::ofstream file_out(file_name, std::ios::out | std::ios::binary);
            file._SerializeOut(file_out);
            file_out.close();
        }
    }

    return 0;
}
