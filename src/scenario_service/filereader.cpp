#include "filereader.h"
#include <iostream>

std::ifstream read_file(const std::filesystem::path &filename) {
  std::ifstream f(filename);
  if (!f) {
    std::ostringstream oss;
    oss << "error reading file " << filename;
    throw std::invalid_argument(oss.str());
  }
  return f;
}

std::vector<std::string> read_map(const std::filesystem::path& filename,
                                  int skip_count = 4) {
  int width;
  std::ifstream f;
  try {
    f = read_file(filename);
  } catch (const std::invalid_argument& e) {
    std::cout << e.what() << std::endl;
    return std::vector<std::string>();
  }
  std::string str;

  while (skip_count > 0 && getline(f, str)) {
    if (str.compare(0, 6, "width ") == 0) {
      width = std::stoi(str.substr(6, std::string::npos));
    }
    skip_count--;
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

std::vector<Scenario> read_scenarios(const std::filesystem::path& filename) {

  std::ifstream f;
  try {
  f = read_file(filename);
  } catch (const std::invalid_argument& e) {
    std::cout << e.what() << std::endl;
    return std::vector<Scenario>();
  }

  std::vector<Scenario> scenarios;

  std::string str;
  getline(f, str);
  if (f.peek() == 'v')
    f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  int i = 0;
  while (getline(f, str)) {
    if (str.empty()) {
      continue;
    }
    std::istringstream iss(str);
    Scenario scenario;
    iss.ignore(std::numeric_limits<std::streamsize>::max(), '\t');
    iss.ignore(std::numeric_limits<std::streamsize>::max(), '\t');
    iss.ignore(std::numeric_limits<std::streamsize>::max(), '\t');
    iss.ignore(std::numeric_limits<std::streamsize>::max(), '\t');
    iss >> scenario.start_x >> scenario.start_y >> scenario.goal_x >>
        scenario.goal_y >> scenario.cost;
    scenario.id = i;
    scenarios.push_back(scenario);
    i++;
  }
  return scenarios;
}
