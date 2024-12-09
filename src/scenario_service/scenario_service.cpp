#include "scenario_service.h"
#include "tools.h"
#include <sstream>
#include <stdexcept>

ScenarioService::ScenarioService(){};

Scenario ScenarioService::get_scenario(const int bucket, const int index) {
  if (bucket < 0 || index < 0) {
    throw std::invalid_argument("invalid scenario argument.");
  }
  return get_scenario(10 * bucket + index);
}

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

std::vector<Scenario> ScenarioService::get_all_scenarios() {
  return scenarios;
}

bool ScenarioService::setMapFile(const std::filesystem::path& i_map_file) {
  if (i_map_file.empty() || !std::filesystem::is_regular_file(i_map_file)) {
    return false;
  }
  std::vector<std::string> citymap_candidate = read_map(i_map_file, 4);
  if (citymap_candidate.empty()) {
    return false;
  }
  map_file = i_map_file;
  citymap = citymap_candidate;
  return true;
}

bool ScenarioService::setScenarioFile(const std::filesystem::path& i_scenario_file) {
  if(i_scenario_file.empty() || !std::filesystem::is_regular_file(i_scenario_file)) {
    return false;
  }
  auto ret_value = read_scenarios(i_scenario_file);
  scenarios = std::get<0>(ret_value);
  bucket_list = std::get<1>(ret_value);
  scenario_file = i_scenario_file;
  return true;
}


std::vector<int> ScenarioService::get_bucket_list() {
  return bucket_list;
}

std::vector<Scenario> ScenarioService::get_bucket_scenarios(int bucket) {
  int start_index = bucket * 10;
  int end_index = bucket * 10 + 9;
  if (start_index < 0 || end_index >= scenarios.size()) {
    std::ostringstream oss;
    oss << "parameter bucket was " << bucket << ", start_index " << start_index << ", end_index " << end_index << std::endl;
    throw std::invalid_argument(oss.str()); 
  }
  return std::vector<Scenario>(scenarios.begin() + start_index, scenarios.begin() + end_index);
}
