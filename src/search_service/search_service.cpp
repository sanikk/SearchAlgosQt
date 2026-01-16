#include "search_service.h"
#include "searches.h"
#include "worker.h"


SearchService::SearchService(
    ScenarioService& i_scenario_service)
    : scenarioService(i_scenario_service) {};

Scenario SearchService::loadScenario(int index) {
  Scenario scen = scenarioService.get_scenario(index);
  return scen;
}



void SearchService::runAstar(int index) {
  Scenario scenario = loadScenario(index);
  const std::vector<std::string>& citymap = scenarioService.get_map();
  auto start = std::chrono::high_resolution_clock::now();
  RetVal ret = astar_search(scenario.start_x, scenario.start_y, scenario.goal_x, scenario.goal_y, citymap);
  auto end = std::chrono::high_resolution_clock::now();
  ret.timing = end - start; 
  if (ret.found) {

  }
}

void SearchService::runFringe(int index) {
  Scenario scenario = loadScenario(index);
  const std::vector<std::string>& citymap = scenarioService.get_map();
  auto start = std::chrono::high_resolution_clock::now();
  RetVal ret = fringe_search(scenario.start_x, scenario.start_y, scenario.goal_x, scenario.goal_y, citymap);
    auto end = std::chrono::high_resolution_clock::now();
    ret.timing = end - start; 

  if (ret.cost.has_value()) {
  
  }
}

std::vector<RetVal> SearchService::runAstarForBucket(int bucket) {
  std::vector<RetVal> retvals;
  std::vector<Scenario> scenario_list = scenarioService.get_bucketScenarios(bucket);
  for (Scenario& scenario : scenario_list) {
    auto start = std::chrono::high_resolution_clock::now();
    RetVal ret = astar_search(scenario.start_x, scenario.start_y, scenario.goal_x, scenario.goal_y, scenarioService.get_map());
    auto end = std::chrono::high_resolution_clock::now();
    ret.timing = end - start; 
    retvals.push_back(ret);
  }
  return retvals;
}

std::vector<RetVal> SearchService::runFringeForBucket(int bucket) {
  std::vector<RetVal> retvals;
  std::vector<Scenario> scenario_list = scenarioService.get_bucketScenarios(bucket);
  for (Scenario& scenario : scenario_list) {
    auto start = std::chrono::high_resolution_clock::now();
    RetVal ret = fringe_search(scenario.start_x, scenario.start_y, scenario.goal_x, scenario.goal_y, scenarioService.get_map());
    auto end = std::chrono::high_resolution_clock::now();
    ret.timing = end - start; 
    retvals.push_back(ret);
  }
  return retvals;
}

std::vector<RetVal> SearchService::runTestVersionForBucket(const int bucket) {
  std::vector<RetVal> retvals;
  std::vector<Scenario> scenario_list = scenarioService.get_bucketScenarios(bucket);
  for (Scenario& scenario : scenario_list) {
    auto start = std::chrono::high_resolution_clock::now();
    RetVal ret = fringe_with_dll(scenario.start_x, scenario.start_y, scenario.goal_x, scenario.goal_y, scenarioService.get_map());
    auto end = std::chrono::high_resolution_clock::now();
    ret.timing = end - start; 
    retvals.push_back(ret);
  }
  return retvals;
}

void SearchService::run_astar_thread(const int scenario_index) { 
  Scenario scenario = loadScenario(scenario_index);
  WorkerRunner w = WorkerRunner();
  w.run_astar(scenario.start_x, scenario.start_y, scenario.goal_x, scenario.goal_y, scenarioService.get_map(), this);
}

void SearchService::run_fringe_thread(const int scenario_index) { 
  Scenario scenario = loadScenario(scenario_index);
  WorkerRunner w = WorkerRunner();
  w.run_fringe(scenario.start_x, scenario.start_y, scenario.goal_x, scenario.goal_y, scenarioService.get_map(), this);
}

