#include "search_service.h"
#include "searches.h"
#include "conversions.h"
// TODO: remove this iostream import, no prints here after dev
#include <iostream>

SearchService::SearchService(
    ScenarioService& i_scenario_service)
    : scenarioService(i_scenario_service) {};

Scenario SearchService::loadScenario(int index) {
  Scenario scen = scenarioService.get_scenario(index);
  return scen;
}


void printRoute(const std::vector<std::pair<int, int>>& route) {
  // TODO: remove this
  for (std::pair<int, int> pari   : route) {
    std::cout << pari.first << "," << pari.second << std::endl;
  }
}

void printRoute(const std::vector<int>& route, const int map_size) {
  // TODO: remove this
  printRoute(pair_route(route, map_size));
}

void SearchService::runAstar(int index) {
  Scenario scenario = loadScenario(index);
  const std::vector<std::string>& citymap = scenarioService.get_map();
  auto start = std::chrono::high_resolution_clock::now();
  RetVal ret = astar_search(scenario.start_x, scenario.start_y, scenario.goal_x, scenario.goal_y, citymap);
  auto end = std::chrono::high_resolution_clock::now();
  ret.timing = end - start; 
  if (ret.found) {
    printRoute(ret.route);
  }
}

void SearchService::runAstar(int bucket, int index) {
  SearchService::runAstar(10 * bucket + index);
}

void SearchService::runFringe(int index) {
  Scenario scenario = loadScenario(index);
  const std::vector<std::string>& citymap = scenarioService.get_map();
  auto start = std::chrono::high_resolution_clock::now();
  RetVal ret = fringe_search(scenario.start_x, scenario.start_y, scenario.goal_x, scenario.goal_y, citymap);
    auto end = std::chrono::high_resolution_clock::now();
    ret.timing = end - start; 

  if (ret.cost.has_value()) {
    //std::cout << ret.cost.value() << std::endl;
    printRoute(ret.route);
  }
}

void SearchService::runFringe(int bucket, int index) {
  SearchService::runFringe(bucket * 10 + index);
}

const double EPSILON = 0.0001;


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


void SearchService::runAstarWithSignals(const int scenario_index, SearchSignals* signalpack) {
}
