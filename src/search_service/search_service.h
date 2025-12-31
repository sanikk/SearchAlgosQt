#pragma once
#include "models.h"
#include "shared_search_tools.h"
#include "scenario_service.h"
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
  void runAstarWithCallbacks(const int scenario_index, RetVal (*visit)(int, int), RetVal (*expand)(int, int));

  std::vector<RetVal> runTestVersionForBucket(const int bucket);
private:
  ScenarioService& scenarioService;
  Scenario loadScenario(const int index);
};
