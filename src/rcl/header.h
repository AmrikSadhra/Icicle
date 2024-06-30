#pragma once

#include "common/raw_data_interface.h"
#include <array>

namespace rcl {
enum class packing_type {
    unknown,
    flat,
    directory,
};

class header : private raw_data_interface {
  public:
    explicit header() = default;
    bool serialise_in(std::ifstream &ifstream) override;
    bool serialise_out(std::ofstream &ofstream) override;
    [[nodiscard]] std::string to_string() const;
    [[nodiscard]] static packing_type get_packing_type(uint32_t _type);
    [[nodiscard]] static std::string packing_type_to_string(packing_type _type);

    // Raw
    char developer[32]{};
    char compile_date[48]{};
    char oem[32]{};
    uint16_t check1{};
    uint16_t type{};
    uint32_t check2{};
    uint32_t file_size{};
    uint32_t unknown2{};
    uint8_t zeroes[128]{};
    uint32_t unknown3{};
    std::array<uint32_t, 4> directory_offset_table_offsets{};
    uint32_t unknown4{};

    // Derived
    packing_type packing_type{packing_type::unknown};
};
} // namespace rcl
