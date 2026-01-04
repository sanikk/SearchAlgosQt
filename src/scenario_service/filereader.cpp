#include "filereader.h"
#include <fstream>

std::ifstream readFile(const std::filesystem::path &filename) {
  std::ifstream f(filename);
  if (!f) {
    throw std::invalid_argument(filename.string());
  }
  return f;
}

std::vector<std::string> readMap(const std::filesystem::path& filename) {
  int width;
  std::ifstream f = readFile(filename);
  std::string str;

  //first loop skips over the map headers until we get to the 'width...' line
  while (getline(f, str)) {
    if (str.compare(0, 6, "width ") == 0) {
      width = std::stoi(str.substr(6, std::string::npos));
      break;
    }
    continue;
  }

  std::vector<std::string> citymap;
  while (getline(f, str)) {
    if (str.empty() || str.size() < width)
      continue;
    citymap.push_back(str.substr(0, width));
  }
  return citymap;
}

std::vector<Scenario> readScenarios(const std::filesystem::path& filename) {
  std::vector<Scenario> scenarios;
  std::ifstream f = readFile(filename);
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

