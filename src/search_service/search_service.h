#pragma once
#include "models.h"
#include "scenario_service.h"

#include <QObject>

class SearchService : public QObject {
  Q_OBJECT
public:
  SearchService(ScenarioService& i_scenario_service);
  void runAstar(const int index);
  void runFringe(int index);
  void astarFullRun();
  void fringeFullRun();
  int fullComparisonRun();
  void fringeDll(int scenario_id);

  std::vector<RetVal> runAstarForBucket(const int bucket);
  std::vector<RetVal> runFringeForBucket(const int bucket);

  void run_astar_thread(const int scenario_index);
  void run_fringe_thread(const int scenario_index);

  std::vector<RetVal> runTestVersionForBucket(const int bucket);

signals:
  void astarVisit(int x, int y);
  void astarExpand(int x, int y);
  void astarGoal(double cost);
  void astarFound(RetVal ret);
  void fringeVisit(int x, int y);
  void fringeExpand(int x, int y);
  void fringeFound(RetVal ret);

private:
  ScenarioService& scenarioService;
  Scenario loadScenario(const int index);
};
