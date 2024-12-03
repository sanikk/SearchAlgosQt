#include "search_service.h"
#include <iostream>

SearchService::SearchService() {}

SearchService::SearchService(
    const ScenarioService &scenario_service)
    : scenario_service(scenario_service) {};

Scenario SearchService::load_scenario(int index) {
  Scenario scen = scenario_service.get_scenario(index);
  std::cout << scen << std::endl;
  return scen;
}


void print_route(std::vector<std::pair<int, int>> route) {
  for (std::pair<int, int> pari   : route) {
    std::cout << pari.first << "," << pari.second << std::endl;
  }
}

void print_route(std::vector<int> route, int map_size) {
  print_route(pair_route(route, map_size));
}

void SearchService::run_astar(int index) {
  Scenario scen = load_scenario(index);
  const std::vector<std::string>& citymap = scenario_service.get_map();
  RetVal retval = astar_search(scen.start_x, scen.start_y, scen.goal_x, scen.goal_y, citymap);
  if (retval.found) {
    std::cout << retval.cost << std::endl;
    print_route(retval.route);
  }
}

void SearchService::run_astar(int bucket, int index) {
  SearchService::run_astar(10 * bucket + index);
}

void SearchService::run_fringe(int index) {
  Scenario scen = load_scenario(index);
  const std::vector<std::string>& citymap = scenario_service.get_map();
  RetVal retval = fringe_search(scen.start_x, scen.start_y, scen.goal_x, scen.goal_y, citymap);

  if (retval.found) {
    std::cout << retval.cost << std::endl;
    print_route(retval.route);
  }
}

void SearchService::run_fringe(int bucket, int index) {
  SearchService::run_fringe(bucket * 10 + index);
}

const double EPSILON = 0.0001;

int SearchService::full_comparison_run() {
  std::vector<Scenario> scenarios = scenario_service.get_all_scenarios();
  const std::vector<std::string>& citymap = scenario_service.get_map();
  for (Scenario scenario : scenarios) {
    RetVal retAstar = astar_search(scenario.start_x, scenario.start_y, scenario.goal_x, scenario.goal_y, citymap);
    RetVal retFringe = fringe_search(scenario.start_x, scenario.start_y, scenario.goal_x, scenario.goal_y, citymap);
    if (retAstar.cost != retFringe.cost) {
      std::cout << retAstar.cost << " != " << retFringe.cost << std::endl; 
    }
  }     
  return 0;
} 
void SearchService::astar_full_run() {

}

void SearchService::fringe_full_run() {
}

void SearchService::fringe_unopt(int scenario_id) {
  //Scenario scen = scenario_service.get_scenario(scenario_id);
  //std::cout << scen << std::endl;
  //fringe_search_unopt(scen.start_x, scen.start_y, scen.goal_x, scen.goal_y, scenario_service.get_map());
}

void SearchService::fringe_dll(int scenario_id) {
  Scenario scen = load_scenario(scenario_id);
  fringe_with_dll(scen.start_x, scen.start_y, scen.goal_x, scen.goal_y, scenario_service.get_map());
}
