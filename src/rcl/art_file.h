#pragma once

#include "common/raw_data_interface.h"
#include "art_file_entry.h"
#include <vector>

namespace rcl {
class art_file : private raw_data_interface {
  public:
    explicit art_file(art_file_entry &_parent, uint32_t _size, bool _is_file_b);
    bool serialise_in(std::ifstream &ifstream) override;
    bool serialise_out(std::ofstream &ofstream) override;

    // Derived
    art_file_entry &parent;
    uint32_t size{};
    std::vector<char> raw_data;
    bool is_file_b{};
};
} // namespace rcl
