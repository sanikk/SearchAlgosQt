#pragma once
#include "models.h"
#include "searches/common/searches_common.h"
#include "scenario_service.h"
#include "searches/astar_search.h"
#include "searches/fringe_search.h"
#include "searches/fringe_unopt.h"
#include "searches/fringe_with_dll.h"


class SearchService {
public:
  // SearchService();
  SearchService(ScenarioService& scenario_service);
  void run_astar(int index);
  void run_astar(int bucket, int index);
  void run_fringe(int index);
  void run_fringe(int bucket, int index);
  void astar_full_run();
  void fringe_full_run();
  int full_comparison_run();
  void fringe_dll(int scenario_id);
  std::vector<RetVal> run_astar_for_bucket(int bucket);
  std::vector<RetVal> run_fringe_for_bucket(int bucket);
private:
  ScenarioService& scenario_service;
  Scenario load_scenario(int index);
};
