#include "search_service.h"
//#include "astar_with_signals.h"
//#include "astar_thread.h"
//#include "search_signals.h"
#include "searches.h"
#include "conversions.h"
#include "worker.h"
#include <iostream>
//#include <qobject.h>

SearchService::SearchService(
    ScenarioService& i_scenario_service)
    : scenarioService(i_scenario_service) {};

Scenario SearchService::loadScenario(int index) {
  Scenario scen = scenarioService.get_scenario(index);
  return scen;
}


void printRoute(const std::vector<std::pair<int, int>>& route) {
  // TODO: remove this
  for (std::pair<int, int> pari   : route) {
//    std::cout << pari.first << "," << pari.second << std::endl;
  }
}

void printRoute(const std::vector<int>& route, const int map_size) {
  // TODO: remove this
  printRoute(pair_route(route, map_size));
}

void SearchService::runAstar(int index) {
  Scenario scenario = loadScenario(index);
  const std::vector<std::string>& citymap = scenarioService.get_map();
  auto start = std::chrono::high_resolution_clock::now();
  RetVal ret = astar_search(scenario.start_x, scenario.start_y, scenario.goal_x, scenario.goal_y, citymap);
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
  const std::vector<std::string>& citymap = scenarioService.get_map();
  auto start = std::chrono::high_resolution_clock::now();
  RetVal ret = fringe_search(scenario.start_x, scenario.start_y, scenario.goal_x, scenario.goal_y, citymap);
    auto end = std::chrono::high_resolution_clock::now();
    ret.timing = end - start; 

  if (ret.cost.has_value()) {
    //std::cout << ret.cost.value() << std::endl;
    printRoute(ret.route);
  }
}

void SearchService::runFringe(int bucket, int index) {
  SearchService::runFringe(bucket * 10 + index);
}

const double EPSILON = 0.0001;


std::vector<RetVal> SearchService::runAstarForBucket(int bucket) {
  std::vector<RetVal> retvals;
  std::vector<Scenario> scenario_list = scenarioService.get_bucketScenarios(bucket);
  for (Scenario& scenario : scenario_list) {
    auto start = std::chrono::high_resolution_clock::now();
    RetVal ret = astar_search(scenario.start_x, scenario.start_y, scenario.goal_x, scenario.goal_y, scenarioService.get_map());
    auto end = std::chrono::high_resolution_clock::now();
    ret.timing = end - start; 
    retvals.push_back(ret);
  }
  return retvals;
}

std::vector<RetVal> SearchService::runFringeForBucket(int bucket) {
  std::vector<RetVal> retvals;
  std::vector<Scenario> scenario_list = scenarioService.get_bucketScenarios(bucket);
  for (Scenario& scenario : scenario_list) {
    auto start = std::chrono::high_resolution_clock::now();
    RetVal ret = fringe_search(scenario.start_x, scenario.start_y, scenario.goal_x, scenario.goal_y, scenarioService.get_map());
    auto end = std::chrono::high_resolution_clock::now();
    ret.timing = end - start; 
    retvals.push_back(ret);
  }
  return retvals;
}

std::vector<RetVal> SearchService::runTestVersionForBucket(const int bucket) {
  std::vector<RetVal> retvals;
  std::vector<Scenario> scenario_list = scenarioService.get_bucketScenarios(bucket);
  for (Scenario& scenario : scenario_list) {
    auto start = std::chrono::high_resolution_clock::now();
    RetVal ret = fringe_with_dll(scenario.start_x, scenario.start_y, scenario.goal_x, scenario.goal_y, scenarioService.get_map());
    auto end = std::chrono::high_resolution_clock::now();
    ret.timing = end - start; 
    retvals.push_back(ret);
  }
  return retvals;
}

void SearchService::run_astar_thread(const int scenario_index) { 
  std::cout << "SearchService " << QThread::currentThread() << std::endl;
  Scenario scenario = loadScenario(scenario_index);
  WorkerRunner(scenario.start_x, scenario.start_y, scenario.goal_x, scenario.goal_y, scenarioService.get_map(), this);

  //AstarThread* at = new AstarThread{scenario.start_x, scenario.start_y, scenario.goal_x, scenario.goal_y, scenarioService.get_map(), this};
  //QObject::connect(at, &SearchThread::finished, at, &SearchThread::deleteLater);
  //at->start();
}


//void SearchService::runAstarWithSignals(const int scenario_index, SearchSignals* signalpack) {
//void SearchService::runAstarWithSignals(const int scenario_index, MapWidget& map_widget) {
// void SearchService::runAstarWithSignals(const int scenario_index) {
//   std::cout << "SearchService " << QObject::thread() << std::endl;
//   Scenario scenario = loadScenario(scenario_index);
// 
// //  runThread(new AstarWorker{scenario.start_x, scenario.start_y, 
// //                                  scenario.goal_x, scenario.goal_y,
// //                                  scenarioService.get_map()});
//   Worker* worker = new AstarWorker{scenario.start_x, scenario.start_y, 
//                                   scenario.goal_x, scenario.goal_y,
//                                   scenarioService.get_map()};
// 
//   QThread* thread = new QThread;
//   worker->moveToThread(thread);
// 
//   QObject::connect(thread, &QThread::started, worker, &Worker::run);
//   QObject::connect(worker, &Worker::finished, thread, &QThread::quit);
//   QObject::connect(thread, &QThread::finished, worker, &QObject::deleteLater);
//   QObject::connect(thread, &QThread::finished, thread, &QObject::deleteLater);
// 
//   QObject::connect(&worker->search_signals, &SearchSignals::visit, this, &SearchService::astarVisit); 
//   QObject::connect(&worker->search_signals, &SearchSignals::expand, this, &SearchService::astarExpand); 
// 
//   std::cout << "SearchSignals " << worker->search_signals.thread() << std::endl;
//   thread->start();
// //   RetVal ret = astar_with_signals(scenario.start_x, scenario.start_y, 
// //                                   scenario.goal_x, scenario.goal_y,
// //                                   scenarioService.get_map(),
// //                                   signalpack);
//   //if (ret.cost.has_value()) {
//     //std::cout << "cost: " << ret.cost.value() << std::endl;
//   //}
// 
// }

// void SearchService::runFringeWithSignals(const int scenario_index, SearchSignals* signalpack) {
//   Scenario scenario = loadScenario(scenario_index);
//   //std::cout << "firing off search in scenario " << scenario_index << std::endl;
//   // RetVal ret = fringe_with_signals(scenario.start_x, scenario.start_y, scenario.goal_x, scenario.goal_y,scenarioService.get_map(),signalpack);
//   //std::cout << ret.found << std::endl;
//   //if (ret.cost.has_value()) {
//     //std::cout << "cost: " << ret.cost.value() << std::endl;
//   //}
// 
// }

// void SearchService::runThread(Worker* worker) {
//   QThread* thread = new QThread;
//   worker->moveToThread(thread);
// 
//   QObject::connect(thread, &QThread::started, worker, &Worker::run);
//   QObject::connect(worker, &Worker::finished, thread, &QThread::quit);
//   QObject::connect(thread, &QThread::finished, worker, &QObject::deleteLater);
//   QObject::connect(thread, &QThread::finished, thread, &QObject::deleteLater);
// 
//   thread->start();
// }
