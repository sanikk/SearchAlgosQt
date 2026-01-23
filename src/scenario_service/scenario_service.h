#pragma once
#include "scenario.h"
#include <vector>
#include <filesystem>

class ScenarioService {

public:
  ScenarioService();
  Scenario& get_scenario(const int index);
  std::vector<int> get_bucketList();
  std::vector<Scenario> get_bucketScenarios(int bucket);
  std::vector<uint8_t>& get_map();
  std::vector<Scenario> get_allScenarios();
  bool setMapFile(const std::filesystem::path& i_map_file);
  bool setScenarioFile(const std::filesystem::path& i_scenario_file);
  int get_map_size();

private:
  std::filesystem::path mapFile;
  std::filesystem::path scenarioFile;
  std::vector<Scenario> scenarios;
  std::vector<int> bucketList;
  int map_size;

  std::vector<uint8_t> citymap;
};

