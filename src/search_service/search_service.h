#pragma once
#include "models.h"
#include "scenario_service.h"
#include "search_signals.h"

#include <QObject>

class SearchService : public QObject {
  Q_OBJECT;
public:
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
  void runAstarWithSignals(const int scenario_index, SearchSignals* signalpack);
  void runFringeWithSignals(const int scenario_index, SearchSignals* signalpack);

  std::vector<RetVal> runTestVersionForBucket(const int bucket);
private:
  ScenarioService& scenarioService;
  Scenario loadScenario(const int index);
};
