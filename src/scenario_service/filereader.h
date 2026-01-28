#pragma once
#include "scenario.h"
#include "map_data.h"

#include <filesystem>
#include <vector>

/// Reads map file at 'filepath' and converts it to an uint8_t vector.
///
/// @param filepath path to the map file
/// @return MapData object with map dimensions and the uint8_t representation of the map as single index vector.
MapData read_map(const std::filesystem::path& filepath);

/// Reads scenario file at 'filepath' and converts them to Scenario objects
///
/// @param filepath path to the scenario file
/// @return a vector of Scenario objects
std::vector<Scenario> read_scenarios(const std::filesystem::path& filepath);
