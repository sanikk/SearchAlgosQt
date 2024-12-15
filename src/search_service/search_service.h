#pragma once
#include "models.h"
#include "shared_search_tools.h"
#include "scenario_service.h"
// TODO: these are all kinds of fucked up:
// #include "searches/astar_search.h"
// #include "searches/fringe_search.h"
// #include "searches/fringe_unopt.h"
// #include "searches/fringe_with_dll.h"
#include "searches.h"

class SearchService {
public:
  // SearchService();
  SearchService(ScenarioService& i_scenario_service);
  void runAstar(const int index);
  void runAstar(const int bucket, const int index);
  void runFringe(int index);
  void runFringe(int bucket, int index);
  void astarFullRun();
  void fringeFullRun();
  int fullComparisonRun();
  void fringeDll(int scenario_id);
  std::vector<RetVal> runAstarForBucket(const int bucket);
  std::vector<RetVal> runFringeForBucket(const int bucket);
private:
  ScenarioService& scenarioService;
  Scenario loadScenario(const int index);
};
