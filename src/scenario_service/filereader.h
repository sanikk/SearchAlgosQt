#pragma once
#include "scenario.h"
#include "map_data.h"

#include <filesystem>
#include <vector>
#include <limits>

constexpr std::streamsize MAX = std::numeric_limits<std::streamsize>::max();

MapData read_map(const std::filesystem::path& filename);
std::vector<Scenario> read_scenarios(const std::filesystem::path& filename);
