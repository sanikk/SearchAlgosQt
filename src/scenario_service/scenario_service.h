#pragma once
#include "models.h"
// #include "tools.h"
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
  std::vector<int> get_bucketList();
  std::vector<Scenario> get_bucketScenarios(int bucket);
  std::vector<std::string> get_map();
  std::vector<Scenario> get_allScenarios();
  bool setMapFile(const std::filesystem::path& i_map_file);
  bool setScenarioFile(const std::filesystem::path& i_scenario_file);
private:
  std::filesystem::path mapFile;
  std::filesystem::path scenarioFile;
  std::vector<std::string> citymap;
  std::vector<Scenario> scenarios;
  std::vector<int> bucketList;
};

