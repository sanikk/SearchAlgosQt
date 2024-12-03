#pragma once
#include "filereader.h"
#include <string>
#include <vector>
#include <stdexcept>

class ScenarioService {

public:
  ScenarioService();
  ScenarioService(const std::string filename);
  Scenario get_scenario(int index);
  Scenario get_scenario(int bucket, int index);
  std::vector<std::string> get_map();
  std::vector<Scenario> get_all_scenarios();
private:
  std::string filename{""};
  std::vector<std::string> citymap;
  std::vector<Scenario> scenarios;
};

