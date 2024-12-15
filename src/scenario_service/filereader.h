#pragma once
#include "models.h"
#include <filesystem>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>


std::vector<std::string> readMap(const std::filesystem::path& filename, int skip_count);
std::tuple<std::vector<Scenario>, std::vector<int>> readScenarios(const std::filesystem::path& filename);
