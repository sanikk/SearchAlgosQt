#pragma once
#include "models.h"
#include "scenario_service.h"

#include <QObject>
#include <QThread>

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

  std::vector<RetVal> runTestVersionForBucket(const int bucket);
// public slots:
//   void astar_visited(int x, int y);
//   void astar_expanded(int x, int y);
//   void astar_goal_found(double cost);
signals:
  void astarVisit(int x, int y);
  void astarExpand(int x, int y);
  void astarGoal(double cost);
  void astarFound(RetVal ret);
private:
  ScenarioService& scenarioService;
  Scenario loadScenario(const int index);
};
