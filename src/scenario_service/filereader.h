#pragma once
#include "scenario.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>


std::vector<std::string> read_map(const std::string &filename, int skip_count);
std::vector<Scenario> read_scenarios(const std::string &filename);
