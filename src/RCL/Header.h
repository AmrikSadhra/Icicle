#pragma once

#include "Common/IRawData.h"

namespace RCL {
class Header : private IRawData {
  public:
    Header() = default;
    explicit Header(std::ifstream &ifstream);
    void _SerializeOut(std::ofstream &ofstream) override;
    std::string ToString();

    enum class Type {
        FLAT,
        DIRECTORY,
        UNKNOWN
    };

    Type GetType (uint32_t _type);
    static std::string ToString(Type _type);

    // Raw
    char developer[32]{};
    char compile_date[48]{};
    char oem[32]{};
    uint16_t check1 {};
    uint16_t type {};
    uint32_t check2 {};
    uint32_t file_size{};
    uint32_t unknown2{};
    uint8_t zeroes[128]{};
    uint32_t unknown3{};
    uint32_t directory_offset_table_offsets[4]{};
    uint32_t unknown4{};

    // Derived
    Type packing_type;

  private:
    bool _SerializeIn(std::ifstream &ifstream) override;
};
} // namespace RCL
