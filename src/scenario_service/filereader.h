#pragma once
#include "models.h"
#include <filesystem>
#include <string>
#include <vector>
#include <fstream>
#include <limits>

constexpr std::streamsize MAX = std::numeric_limits<std::streamsize>::max();

std::vector<std::string> readMap(const std::filesystem::path& filename);
std::vector<Scenario> readScenarios(const std::filesystem::path& filename);
