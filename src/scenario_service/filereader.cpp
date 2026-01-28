#include "filereader.h"
#include "cell_flags.h"

#include <fstream>
#include <sstream>
#include <string>

#include <iostream>

std::ifstream read_file(const std::filesystem::path &filename) {
  std::ifstream f(filename);
  if (!f) {
    throw std::invalid_argument(filename.string());
  }
  return f;
}

MapData read_map(const std::filesystem::path& filename) {
  int width;
  std::ifstream f = read_file(filename);
  std::string str;

  //first loop skips over the map headers until we get to the 'width...' line
  int height = 0;
  while (std::getline(f, str)) {
    if (str.compare(0, 6, "width ") == 0) {
      width = std::stoi(str.substr(6, std::string::npos));
      break;
    }
    continue;
  }
  std::vector<uint8_t> citymap;
  while (getline(f, str)) {
    if (str.empty() || str.size() < width) {
      continue;
    }
    height++;
    for (char c : str) {
      if (c=='\n' || c=='\r') {
        continue;
      }
      citymap.push_back(c == '@' ? WALL: 0u);
    }
  }
  return MapData(height, width, citymap);
}

std::vector<Scenario> read_scenarios(const std::filesystem::path& filename) {
  std::vector<Scenario> scenarios;
  std::ifstream f = read_file(filename);
  std::string str;
  std::string trash;
  int i = 0;
  int bucket;
  while (getline(f, str)) {
    if (str[0] == 'v' || str.empty()) {
      continue;
    }
    std::istringstream iss(str);
    Scenario scenario;
    iss >> scenario.bucket >> trash >> trash >> trash >> scenario.start_x >> scenario.start_y >> scenario.goal_x >>
        scenario.goal_y >> scenario.cost;
    scenario.id = i;
    scenarios.push_back(scenario);
    i++;
  }
  return scenarios;
}

