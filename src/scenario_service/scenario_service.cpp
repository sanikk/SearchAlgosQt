#include "scenario_service.h"
#include "filereader.h"


ScenarioService::ScenarioService() {};

Scenario ScenarioService::get_scenario(const int index)
{
  if (index < 0 || index >= scenarios.size()) {
    throw std::invalid_argument("invalid scenario number.");
  }
  return scenarios[index];
}

std::vector<std::string> ScenarioService::get_map(){
  return citymap;
}

std::vector<Scenario> ScenarioService::get_allScenarios() {
  return scenarios;
}

bool ScenarioService::setMapFile(const std::filesystem::path& i_map_file) {
  if (i_map_file.empty() || !std::filesystem::is_regular_file(i_map_file)) {
    return false;
  }
  std::vector<std::string> citymap_candidate = readMap(i_map_file);
  if (citymap_candidate.empty()) {
    return false;
  }
  mapFile = i_map_file;
  citymap = citymap_candidate;
  return true;
}

bool ScenarioService::setScenarioFile(const std::filesystem::path& i_scenario_file) {
  if(i_scenario_file.empty() || !std::filesystem::is_regular_file(i_scenario_file)) {
    return false;
  }
  scenarios = readScenarios(i_scenario_file);
  bucketList.clear();
  int previous_bucket = -1;
  for (Scenario scenario: scenarios) {
    if (scenario.bucket != previous_bucket) {
      bucketList.push_back(scenario.bucket);
      previous_bucket = scenario.bucket;
    }
  }
  scenarioFile = i_scenario_file;
  return true;
}

std::vector<int> ScenarioService::get_bucketList() {
  return bucketList;
}

std::vector<Scenario> ScenarioService::get_bucketScenarios(int bucket) {
  std::vector<Scenario> returnable;
  for (Scenario scenario : scenarios) {
    if (scenario.bucket == bucket) {
      returnable.push_back(scenario);
    }
  }
  return returnable;
}
