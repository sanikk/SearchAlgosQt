#include "filereader.h"
#include <iostream>


long MAX = std::numeric_limits<std::streamsize>::max();


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
  
  f = read_file(filename);
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

std::tuple<std::vector<Scenario>, std::vector<int>> read_scenarios(const std::filesystem::path& filename) {

  std::ifstream f;
  std::tuple<std::vector<Scenario>, std::vector<int>> returnable;

  f = read_file(filename);
  std::string str;
  getline(f, str);
  if (f.peek() == 'v')
    f.ignore(MAX, '\n');

  int i = 0;
  int bucket;
  int previous_bucket = -1;
  while (getline(f, str)) {
    if (str.empty()) {
      continue;
    }
    std::istringstream iss(str);
    Scenario scenario;
    iss >> bucket;
    if (bucket != previous_bucket) {
      std::get<1>(returnable).push_back(bucket);
      previous_bucket = bucket;
    }
    iss.ignore(MAX, '\t');
    iss.ignore(MAX, '\t');
    iss.ignore(MAX, '\t');
    iss.ignore(MAX, '\t');
    iss >> scenario.start_x >> scenario.start_y >> scenario.goal_x >>
        scenario.goal_y >> scenario.cost;
    scenario.id = i;
    std::get<0>(returnable).push_back(scenario);
    i++;
  }
  return returnable;
}

