#include <filesystem>
#include <format>
#include <iostream>
#include <optional>
#include <vector>

#include "rcl/rcl_file.h"

using namespace rcl;
namespace fs = std::filesystem;

int main(int argc, char **argv) {
    std::vector<std::string> const args(argv + 1, argv + argc);
    if (args.size() < 2 || args[0] == "help") {
        std::cerr << "Icicle requires 2 arguments: [path_to_rcl_file] [output_directory] [opt:rcl_out_file_name]"
                  << std::endl;
        return EINVAL;
    }

    std::string const &rcl_path{args[0]};
    std::string const &output_dir{args[1]};
    auto const &rcl_out_file_name{(args.size() == 3) ? std::optional<std::string>(args[3]) : std::nullopt};

    std::ifstream clarion_rcl(rcl_path, std::ios::in | std::ios::binary);
    if (!clarion_rcl.is_open()) {
        std::cerr << "Couldn't open RCL file at: " << rcl_path << std::endl;
        return ENOENT;
    }

    if ((!fs::is_directory(output_dir) || !fs::exists(output_dir)) && !fs::create_directory(output_dir)) {
        std::cerr << "Couldn't create output directory: " << output_dir << std::endl;
        return ENOENT;
    }

    rcl_file rcl_file;
    if (!rcl_file.serialise_in(clarion_rcl)) {
        std::cerr << "Failed to serialise RCL file from " << rcl_path << " to memory" << std::endl;
        return 1;
    }
    size_t const num_dumped_files{rcl_file::dump_art_files(rcl_file, output_dir)};
    std::cout << "Successfully dumped " << num_dumped_files << " files from " << rcl_path << " to " << output_dir
              << std::endl;

    if (rcl_out_file_name.has_value()) {
        std::string const rcl_test_file_path{std::format("{}/test", output_dir)};
        std::ofstream rcl_test_file(rcl_test_file_path, std::ios::out | std::ios::binary);
        if (!rcl_file.serialise_out(rcl_test_file)) {
            std::cerr << "Failed to serialise RCL file to " << rcl_test_file_path << " from " << rcl_path
                      << " back out to disk" << std::endl;
            rcl_test_file.close();
            return 1;
        }
        rcl_test_file.close();
    }

    return 0;
}
