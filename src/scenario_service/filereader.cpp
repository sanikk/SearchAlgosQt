#include "filereader.h"
#include <iostream>

std::ifstream read_file(const std::string &filename) {
  std::ifstream f(filename);
  if (!f) {
    std::cout << "error reading " << filename << '\n';
    throw std::invalid_argument("error reading file");
  }
  return f;
}

std::vector<std::string> read_map(const std::string &filename,
                                  int skip_count = 4) {
  int width;
  std::ifstream f = read_file(filename);
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

std::vector<Scenario> read_scenarios(const std::string &filename) {
  std::ifstream f = read_file(filename);

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
