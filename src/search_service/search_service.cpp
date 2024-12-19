#include "search_service.h"
#include "fringe_with_linked_map_pairs.h"
#include <iostream>

SearchService::SearchService(ScenarioService &i_scenario_service)
    : scenarioService(i_scenario_service) {};

Scenario SearchService::loadScenario(int index) {
  Scenario scen = scenarioService.get_scenario(index);
  std::cout << scen << std::endl;
  return scen;
}

void printRoute(const std::vector<std::pair<int, int>> &route) {
  for (std::pair<int, int> pari : route) {
    std::cout << pari.first << "," << pari.second << std::endl;
  }
}

void printRoute(const std::vector<int> &route, const int map_size) {
  printRoute(pair_route(route, map_size));
}

void SearchService::runAstar(int index) {
  Scenario scenario = loadScenario(index);
  const std::vector<std::string> &citymap = scenarioService.get_map();
  auto start = std::chrono::high_resolution_clock::now();
  RetVal ret = astar_search(scenario.start_x, scenario.start_y, scenario.goal_x,
                            scenario.goal_y, citymap);
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
  const std::vector<std::string> &citymap = scenarioService.get_map();
  auto start = std::chrono::high_resolution_clock::now();
  RetVal ret = fringe_search(scenario.start_x, scenario.start_y,
                             scenario.goal_x, scenario.goal_y, citymap);
  auto end = std::chrono::high_resolution_clock::now();
  ret.timing = end - start;

  if (ret.cost.has_value()) {
    std::cout << ret.cost.value() << std::endl;
    printRoute(ret.route);
  }
}

void SearchService::runFringe(int bucket, int index) {
  SearchService::runFringe(bucket * 10 + index);
}

const double EPSILON = 0.0001;

// int SearchService::full_comparison_run() {
//   std::vector<Scenario> scenarios = scenario_service.get_all_scenarios();
//   const std::vector<std::string>& citymap = scenario_service.get_map();
//   for (Scenario scenario : scenarios) {
//     RetVal retAstar = astar_search(scenario.start_x, scenario.start_y,
//     scenario.goal_x, scenario.goal_y, citymap); RetVal retFringe =
//     fringe_search(scenario.start_x, scenario.start_y, scenario.goal_x,
//     scenario.goal_y, citymap); if (retAstar.cost != retFringe.cost) {
//       std::cout << retAstar.cost.value() << " != " << retFringe.cost.value()
//       << std::endl;
//     }
//   }
//   return 0;
// }

std::vector<RetVal> SearchService::runAstarForBucket(int bucket) {
  std::vector<RetVal> retvals;
  std::vector<Scenario> scenario_list =
      scenarioService.get_bucketScenarios(bucket);
  for (Scenario &scenario : scenario_list) {
    auto start = std::chrono::high_resolution_clock::now();
    RetVal ret =
        astar_search(scenario.start_x, scenario.start_y, scenario.goal_x,
                     scenario.goal_y, scenarioService.get_map());
    auto end = std::chrono::high_resolution_clock::now();
    ret.timing = end - start;
    retvals.push_back(ret);
  }
  return retvals;
}

std::vector<RetVal> SearchService::runFringeForBucket(int bucket) {
  std::vector<RetVal> retvals;
  std::vector<Scenario> scenario_list =
      scenarioService.get_bucketScenarios(bucket);
  for (Scenario &scenario : scenario_list) {
    auto start = std::chrono::high_resolution_clock::now();
    RetVal ret =
        fringe_search(scenario.start_x, scenario.start_y, scenario.goal_x,
                      scenario.goal_y, scenarioService.get_map());
    auto end = std::chrono::high_resolution_clock::now();
    ret.timing = end - start;
    retvals.push_back(ret);
  }
  return retvals;
}

std::vector<RetVal> SearchService::runTestVersionForBucket(const int bucket) {
  std::vector<RetVal> retvals;
  std::vector<Scenario> scenario_list =
      scenarioService.get_bucketScenarios(bucket);
  for (Scenario &scenario : scenario_list) {
    auto start = std::chrono::high_resolution_clock::now();
    RetVal ret = fringe_with_linked_map_pairs(
        scenario.start_x, scenario.start_y, scenario.goal_x, scenario.goal_y,
        scenarioService.get_map());
    auto end = std::chrono::high_resolution_clock::now();
    ret.timing = end - start;
    retvals.push_back(ret);
  }
  return retvals;
}
