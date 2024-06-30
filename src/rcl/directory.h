#pragma once

#include "art_file.h"
#include "art_file_entry.h"
#include "common/raw_data_interface.h"

namespace rcl {
class directory : private raw_data_interface {
  public:
    explicit directory(bool _directory_hierarchy);
    bool serialise_in(std::ifstream &ifstream) override;
    bool serialise_out(std::ofstream &ofstream) override;
    [[nodiscard]] std::string to_string() const;

    // Raw
    uint32_t size{};
    std::vector<art_file_entry> art_file_entries;
    std::vector<art_file> art_files;

    // Derived
    bool directory_hierarchy{};
    uint32_t num_files{};

  private:
    static bool _check_for_png_header(std::ifstream &ifstream);
    static constexpr uint32_t PNG_HEADER{0x474E5089};
};
} // namespace rcl
