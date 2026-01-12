#pragma once
//#include "worker.h"
#include "models.h"
#include "scenario_service.h"
//#include "search_signals.h"
// #include "map_widget.h"

#include <QObject>
#include <QThread>

class SearchService : public QObject {
  Q_OBJECT
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

  // void runAstarWithSignals(const int scenario_index);
  void run_astar_thread(const int scenario_index);

  std::vector<RetVal> runTestVersionForBucket(const int bucket);
signals:
  void astarVisit(int x, int y);
  void astarExpand(int x, int y);
  void astarFound(RetVal ret);
private:
  ScenarioService& scenarioService;
  Scenario loadScenario(const int index);
};
