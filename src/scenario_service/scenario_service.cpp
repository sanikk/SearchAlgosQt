#include "scenario_service.h"
#include "map_data.h"
#include "filereader.h"


ScenarioService::ScenarioService(int width, int height) 
  : width(width), height(height) { citymap.assign(width * height, 0); };

Scenario& ScenarioService::get_scenario(int scenario_index)
{
  if (scenario_index < 0 || scenario_index >= scenarios.size()) {
    throw std::invalid_argument("invalid scenario number.");
  }
  return scenarios[scenario_index];
}

bool ScenarioService::set_map_file(const std::filesystem::path& i_map_file) {
  if (i_map_file.empty() || !std::filesystem::is_regular_file(i_map_file)) {
    return false;
  }
  MapData md = read_map(i_map_file);
  if (md.map_data.empty()) {
    return false;
  }
  map_file = i_map_file;
  citymap = md.map_data;
  width = md.width;
  height = md.height;
  return true;
}

bool ScenarioService::set_scenario_file(const std::filesystem::path& i_scenario_file) {
  if(i_scenario_file.empty() || !std::filesystem::is_regular_file(i_scenario_file)) {
    return false;
  }
  scenarios = read_scenarios(i_scenario_file);
  bucket_list.clear();
  int previous_bucket = -1;
  for (Scenario scenario: scenarios) {
    if (scenario.bucket != previous_bucket) {
      bucket_list.push_back(scenario.bucket);
      previous_bucket = scenario.bucket;
    }
  }
  scenario_file = i_scenario_file;
  return true;
}


std::vector<Scenario> ScenarioService::get_bucket_scenarios(int bucket) {
  std::vector<Scenario> returnable;
  for (Scenario scenario : scenarios) {
    if (scenario.bucket == bucket) {
      returnable.push_back(scenario);
    }
  }
  return returnable;
}

void ScenarioService::clear() {
  citymap.clear();
  citymap.resize(0);
  scenarios.clear();
  scenarios.resize(0);
}
