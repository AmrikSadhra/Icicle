#pragma once

#include "common/raw_data_interface.h"

namespace rcl {
class art_file_entry : private raw_data_interface {
  public:
    explicit art_file_entry(size_t _id);
    bool serialise_in(std::ifstream &ifstream) override;
    bool serialise_out(std::ofstream &ofstream) override;
    [[nodiscard]] std::string to_string() const;

    // Raw
    uint32_t offset{};
    uint32_t offset_2{};
    uint32_t num_bytes{};
    uint32_t num_bytes_2{};

    // Derived
    size_t id{};
    bool multi_file{};
};
} // namespace rcl
