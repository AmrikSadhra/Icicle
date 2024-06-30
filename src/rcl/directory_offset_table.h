#pragma once

#include "common/raw_data_interface.h"
#include <array>

namespace rcl {
class directory_offset_table : private raw_data_interface {
  public:
    directory_offset_table() = default;
    bool serialise_in(std::ifstream &ifstream) override;
    bool serialise_out(std::ofstream &ofstream) override;

    // Raw
    uint32_t magic_0128{};
    std::array<uint32_t, 73> directory_offsets{};

  private:
    static constexpr uint32_t DIR_OFFSET_TABLE_MAGIC{0x00000128};
};
} // namespace rcl
