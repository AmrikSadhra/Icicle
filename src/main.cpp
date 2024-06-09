#include <filesystem>
#include <iostream>
#include <vector>

namespace fs = std::filesystem;

#include "RCL/RclFile.h"

uint32_t DumpArtFiles(std::string const &output_dir, RCL::RclFile &rcl_file) {
    uint32_t num_dumped_files{0};
    for (uint32_t directory_id{0}; directory_id < rcl_file.directories.size(); ++directory_id) {
        RCL::Directory &file_table{rcl_file.directories[directory_id]};
        for (uint32_t file_id{0}; file_id < file_table.num_files; ++file_id) {
            RCL::ArtFile &art_file{file_table.art_files[file_id]};
            if (art_file.size == 0)
                continue;
            std::string art_file_name{std::to_string(directory_id) + "_" + std::to_string(file_id) + ".png"};
            std::ofstream art_file_out(output_dir + "/" + art_file_name, std::ios::out | std::ios::binary);
            art_file._SerializeOut(art_file_out);
            art_file_out.close();
            ++num_dumped_files;
        }
    }
    return num_dumped_files;
}

int main(int argc, char **argv) {
    std::vector<std::string> args(argv + 1, argv + argc);
    if (args.size() < 2) {
        std::cerr << "Icicle requires 2 arguments: [path_to_rcl_file] [output_directory]" << std::endl;
    }

    const std::string &rcl_path{args[0]};
    const std::string &output_dir{args[1]};

    std::ifstream clarion_rcl(rcl_path, std::ios::in | std::ios::binary);
    if (!clarion_rcl.is_open()) {
        std::cerr << "Couldn't open RCL file at: " << rcl_path << std::endl;
        return 1;
    }

    if (!fs::is_directory(output_dir) || !fs::exists(output_dir)) {
        fs::create_directory(output_dir);
    }

    RCL::RclFile rcl_file(clarion_rcl);
    uint32_t const num_dumped_files{DumpArtFiles(output_dir, rcl_file)};
    std::cout << "Successfully dumped " << num_dumped_files << " files from " << rcl_path << std::endl;

    return 0;
}
