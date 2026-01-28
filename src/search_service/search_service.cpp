#include "search_service.h"
#include "worker.h"
#include "conversions.h"


SearchService::SearchService(
    ScenarioService& i_scenario_service)
    : scenario_service(i_scenario_service), citymap(i_scenario_service.get_map())
{
    clear_storage();
};

std::vector<int> SearchService::get_map_frame(bool show_astar, bool show_fringe) {
  std::vector<int> returnable;
  for (int i=0; i < citymap.size(); i++) {
    uint8_t byte = citymap[i]; 
    if (show_astar) {
      if (byte & EXPAND_A) {
        returnable.push_back(7);
        continue;
      }
      if (byte & VISIT_A) {
        returnable.push_back(6);
        continue;
      }
    }
    if (show_fringe) {
      if (byte & EXPAND_F)  {
        returnable.push_back(5);
        continue;
      }
      if (byte & VISIT_F)  {
        returnable.push_back(4);
        continue;
      }
    }
    if (byte & START)  {
        returnable.push_back(2);
        continue;
    }
    if (byte & GOAL)  {
        returnable.push_back(3);
        continue;
    }
    if (byte & WALL)  {
        returnable.push_back(1);
        continue;
      }
    returnable.push_back(0);
  }

  return returnable;
}

void SearchService::set_map() {
  clear_storage();
}

void SearchService::reset_counters() {
  astar_visits = 0;
  astar_expands = 0;
  astar_cost = 0.0;
  fringe_visits = 0;
  fringe_expands = 0;
  fringe_cost = 0.0;
  fringe_flimit = 0.0;
}

void SearchService::clear_storage() {
  reset_counters();
  scenario_service.clear();
}

void SearchService::clear_scenario() {
  reset_counters();
  if (citymap.empty()) return;
  for (int i=0;i < citymap.size(); i++) {
    citymap[i] &= CLEAR_SCENARIO;
  }
}

void SearchService::load_scenario(int index) {
  Scenario& scen = scenario_service.get_scenario(index);
  clear_scenario();
  set_start_goal(scen);
}

void SearchService::set_start_goal(Scenario& scenario) {
  auto[width, height] = scenario_service.get_map_size();
  for (int i=-2; i<3; i++) {
    citymap[xy2int(std::max(0, std::min(scenario.start_x + i, width - 1)), scenario.start_y, width)] |= START;
    citymap[xy2int(scenario.start_x, std::max(0, std::min(scenario.start_y + i, height - 1)), width)] |= START;

    citymap[xy2int(std::max(0, std::min(scenario.goal_x + i, width - 1)), scenario.goal_y, width)] |= GOAL;
    citymap[xy2int(scenario.goal_x, std::max(0, std::min(scenario.goal_y + i, height - 1)), width)] |= GOAL;
  }
}



void SearchService::run_astar(int scenario_index) {
  Scenario& scenario = scenario_service.get_scenario(scenario_index);
  //const std::vector<std::string>& citymap = scenario_service.get_map();
  auto start = std::chrono::high_resolution_clock::now();
//  RetVal ret = astar_search(scenario.start_x, 
//                            scenario.start_y, scenario.goal_x, scenario.goal_y, citymap);
  auto end = std::chrono::high_resolution_clock::now();
//  ret.timing = end - start; 
//  if (ret.found) {
//  }
}

void SearchService::run_fringe(int scenario_index) {
  Scenario& scenario = scenario_service.get_scenario(scenario_index);
  //const std::vector<std::string>& citymap = scenario_service.get_map();
  auto start = std::chrono::high_resolution_clock::now();
  //RetVal ret = fringe_search(scenario.start_x, scenario.start_y, scenario.goal_x, scenario.goal_y, citymap);
  auto end = std::chrono::high_resolution_clock::now();
  //ret.timing = end - start; 

  //if (ret.cost.has_value()) {
  //}
}

std::vector<RetVal> SearchService::run_astar_for_bucket(int bucket_index) {
  std::vector<RetVal> retvals;
  std::vector<Scenario> scenario_list = scenario_service.get_bucket_scenarios(bucket_index);
  for (Scenario& scenario : scenario_list) {
    auto start = std::chrono::high_resolution_clock::now();
    //RetVal ret = astar_search(scenario.start_x, scenario.start_y, scenario.goal_x, scenario.goal_y, scenario_service.get_map());
    auto end = std::chrono::high_resolution_clock::now();
    //ret.timing = end - start; 
    //retvals.push_back(ret);
  }
  return retvals;
}

std::vector<RetVal> SearchService::run_fringe_for_bucket(int bucket_index) {
  std::vector<RetVal> retvals;
  std::vector<Scenario> scenario_list = scenario_service.get_bucket_scenarios(bucket_index);
  for (Scenario& scenario : scenario_list) {
    auto start = std::chrono::high_resolution_clock::now();
    //RetVal ret = fringe_search(scenario.start_x, scenario.start_y, scenario.goal_x, scenario.goal_y, scenario_service.get_map());
    auto end = std::chrono::high_resolution_clock::now();
    //ret.timing = end - start; 
    //retvals.push_back(ret);
  }
  return retvals;
}

std::vector<RetVal> SearchService::run_test_version_for_bucket(const int bucket_index) {
  std::vector<RetVal> retvals;
  std::vector<Scenario> scenario_list = scenario_service.get_bucket_scenarios(bucket_index);
  for (Scenario& scenario : scenario_list) {
    auto start = std::chrono::high_resolution_clock::now();
    //RetVal ret = fringe_with_dll(scenario.start_x, scenario.start_y, scenario.goal_x, scenario.goal_y, scenario_service.get_map());
    auto end = std::chrono::high_resolution_clock::now();
    //ret.timing = end - start; 
    //retvals.push_back(ret);
  }
  return retvals;
}

void SearchService::run_astar_thread(const int scenario_index) { 
  auto[width, height] = scenario_service.get_map_size();
  Scenario& scenario = scenario_service.get_scenario(scenario_index);
  WorkerRunner w = WorkerRunner();
  w.run_astar(scenario.start_x, scenario.start_y, scenario.goal_x, scenario.goal_y, width, 
              height, scenario_service.get_map(), this);
}

void SearchService::run_fringe_thread(const int scenario_index) { 
  auto[width, height] = scenario_service.get_map_size();
  Scenario& scenario = scenario_service.get_scenario(scenario_index);
  WorkerRunner w = WorkerRunner();
  //w.run_fringe(scenario.start_x, scenario.start_y, scenario.goal_x, scenario.goal_y, scenario_service.get_map(), this);
}

void SearchService::visit_astar_slot(int x, int y) {
  auto[width, _] = scenario_service.get_map_size();
  uint8_t& cell = citymap[xy2int(x,y,width)];
  cell |= VISIT_A;
  astar_visits++;
  if (!(cell & EXPAND_A)) {
    emit visit_astar_signal(x, y);
  }
}

void SearchService::expand_astar_slot(int x, int y) {
  auto[width, _] = scenario_service.get_map_size();
    uint8_t& cell = citymap[xy2int(x,y,width)];
    cell |= EXPAND_A;
    astar_expands++;
    emit expand_astar_signal(x, y);
}

void SearchService::found_astar_slot(RetVal ret) {
  if (ret.cost.has_value()) astar_cost = ret.cost.value();
  emit found_astar_signal(ret);
}

void SearchService::visit_fringe_slot(int x, int y) {
  auto[width, _] = scenario_service.get_map_size();
  uint8_t& cell = citymap[xy2int(x,y,width)];
  cell |= VISIT_F;
  fringe_visits++;
  if (!(cell & EXPAND_F)) {
    emit visit_fringe_signal(x, y);
  }
}

void SearchService::expand_fringe_slot(int x, int y) {
  auto[width, _] = scenario_service.get_map_size();
  uint8_t& cell = citymap[xy2int(x,y,width)];
  cell |= EXPAND_F;
  fringe_expands++;
  emit expand_fringe_signal(x, y);
}

void SearchService::found_fringe_slot(RetVal ret) {
  if (ret.cost.has_value()) fringe_cost = ret.cost.value();
  emit found_fringe_signal(ret);
}

void SearchService::reset_astar() {
    astar_visits = 0;
    astar_expands = 0;
    astar_cost = 0;
}

void SearchService::reset_fringe() {
    fringe_visits = 0;
    fringe_expands = 0;
    fringe_cost = 0;
}
