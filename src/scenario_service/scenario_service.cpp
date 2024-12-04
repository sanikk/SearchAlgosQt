#include "scenario_service.h"
#include "filereader.h"
#include <filesystem>
#include <iostream>


ScenarioService::ScenarioService(){};

Scenario ScenarioService::get_scenario(int bucket, int index) {
  if (bucket < 0 || index < 0) {
    std::cerr << "bucket and index have to be positive ints." << std::endl;
    throw std::invalid_argument("invalid scenario argument.");
  }
  return get_scenario(10 * bucket + index);
}

Scenario ScenarioService::get_scenario(int index)
{
  if (index < 0 || index >= scenarios.size()) {
    throw std::invalid_argument("invalid scenario number.");
  }
  return scenarios[index];
}

std::vector<std::string> ScenarioService::get_map(){
  return citymap;
}

std::vector<Scenario> ScenarioService::get_all_scenarios() {
  return scenarios;
}

bool ScenarioService::setMapFile(std::filesystem::path i_map_file) {
  if (i_map_file.empty() || !std::filesystem::is_regular_file(i_map_file)) {
    return false;
  }
  map_file = i_map_file;
  citymap = read_map(i_map_file, 4);
  return true;
}

bool ScenarioService::setScenarioFile(std::filesystem::path i_scenario_file) {
  if(i_scenario_file.empty() || !std::filesystem::is_regular_file(i_scenario_file)) {
    return false;
  }
  scenario_file = i_scenario_file;
  scenarios = read_scenarios(i_scenario_file);
  return true;
}
