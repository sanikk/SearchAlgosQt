#include "scenario_service.h"
#include <iostream>


ScenarioService::ScenarioService(){};

ScenarioService::ScenarioService(std::string filename)
    : filename(filename), scenarios(read_scenarios(filename + ".scen")),
      citymap(read_map(filename, 4)) {}

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
