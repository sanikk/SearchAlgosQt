#pragma once
#include "scenario.h"
#include <filesystem>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>


std::vector<std::string> read_map(const std::filesystem::path &filename, int skip_count);
std::tuple<std::vector<Scenario>, std::vector<int>> read_scenarios(const std::filesystem::path &filename);
