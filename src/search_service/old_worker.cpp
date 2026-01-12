#include "worker.h"
#include "search_signals.h"
#include "searches.h"

#include <iostream>

//AstarWorker::AstarWorker(const int startx, const int starty, const int goalx, const int goaly, const std::vector<std::string>& citymap, SearchSignals* search_signals) : Worker(startx, starty, goalx, goaly, citymap, search_signals) {
AstarWorker::AstarWorker(const int startx, const int starty, const int goalx, const int goaly, const std::vector<std::string>& citymap) : Worker(startx, starty, goalx, goaly, citymap) {
}

void AstarWorker::run() {
  std::cout << "AstarWorker " << QObject::thread() << std::endl;
  astar_with_signals(startx, starty, goalx, goaly, citymap, &search_signals);
  emit finished();
}

FringeWorker::FringeWorker(const int startx, const int starty, const int goalx, const int goaly, const std::vector<std::string>& citymap) : Worker(startx, starty, goalx, goaly, citymap) {
}

void FringeWorker::run() {
  //fringe_with_signals(startx, starty, goalx, goaly, citymap, search_signals);
  emit finished();
}

Worker::Worker(const int startx, const int starty, const int goalx, const int goaly, const std::vector<std::string>& citymap) : 
  startx(startx), starty(starty), goalx(goalx), 
  goaly(goaly), citymap(citymap), search_signals(SearchSignals(this)) {}

