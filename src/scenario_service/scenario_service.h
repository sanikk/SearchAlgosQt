#pragma once
#include "scenario.h"
#include "filereader.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <filesystem>

class ScenarioService {

public:
  ScenarioService();
  Scenario get_scenario(const int index);
  Scenario get_scenario(const int bucket, const int index);
  std::vector<std::string> get_map();
  std::vector<Scenario> get_all_scenarios();
  bool setMapFile(const std::filesystem::path &i_map_file);
  bool setScenarioFile(const std::filesystem::path &i_scenario_file);
private:
  std::filesystem::path map_file;
  std::filesystem::path scenario_file;
  std::vector<std::string> citymap;
  std::vector<Scenario> scenarios;
};

