#pragma once
//#include "models.h"
#include "scenario.h"
#include "map_data.h"

#include <filesystem>
#include <vector>
#include <limits>

constexpr std::streamsize MAX = std::numeric_limits<std::streamsize>::max();

MapData readMap(const std::filesystem::path& filename);
std::vector<Scenario> readScenarios(const std::filesystem::path& filename);
