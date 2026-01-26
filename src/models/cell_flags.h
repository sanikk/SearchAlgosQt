#pragma once
#include <cstdint>

enum CellFlags : std::uint8_t {
  WALL      = 1u << 7,
  START     = 1u << 6,
  GOAL      = 1u << 5,
  VISIT_F   = 1u << 4,
  EXPAND_F  = 1u << 3,
  VISIT_A   = 1u << 2,
  EXPAND_A  = 1u << 1,
  FOUND     = 1u << 0
};

