#include "worker.h"
#include "models.h"
#include "children.h"
#include "heuristics.h"
#include "conversions.h"
#include "retval.h"

#include <queue>

#include <QThread>


WorkerRunner::WorkerRunner(int startx, int starty, int goalx, int goaly, 
                           const std::vector<std::string>& citymap, 
                           SearchService* search_service) {

  QThread* thread = new QThread;
  AstarWorker* worker = new AstarWorker{startx, starty, goalx, goaly, citymap};
  worker->moveToThread(thread);

  connect(thread, &QThread::started, worker, &AstarWorker::run);
  connect(worker, &AstarWorker::finished, thread, &QThread::quit);
  connect(worker, &AstarWorker::finished, worker, &QObject::deleteLater);
  connect(thread, &QThread::finished, thread, &QObject::deleteLater);
  
  connect(worker, &AstarWorker::visit_node, search_service, &SearchService::astarVisit, Qt::QueuedConnection);
  connect(worker, &AstarWorker::expand_node, search_service, &SearchService::astarExpand, Qt::QueuedConnection);
  //connect(worker, &AstarWorker::found_cost, search_service, &SearchService::astarGoal, Qt::QueuedConnection);
  connect(worker, &AstarWorker::found_goal, search_service, &SearchService::astarFound, Qt::QueuedConnection);

  thread->start();
}





AstarWorker::AstarWorker(int startx, int starty, int goalx, int goaly, const std::vector<std::string>& i_citymap)
: startx(startx), starty(starty), goalx(goalx), goaly(goaly), citymap(i_citymap) {
}

void AstarWorker::run() {
  astar_with_signals();
  emit finished();
}

void AstarWorker::astar_with_signals() {
  Node start_node{startx, starty};
  Node goal_node{goalx, goaly};
  start_node.cost = SearchTools::heuristics(start_node, goal_node);

  std::priority_queue<Node, std::vector<Node>, std::greater<Node>> heap;
  heap.push(start_node);
  
  int map_size = citymap.size(); 
  int start_index = xy2int(start_node, map_size);
  std::unordered_map<int, double> gscores;
  gscores[start_index] = 0.0;
  std::unordered_map<int, int> camefrom;
  camefrom[start_index] = -1;

  while (!heap.empty()) {
    Node current = heap.top();
    heap.pop();

    emit expand_node(current.x, current.y);
    
    int current_index = xy2int(current, map_size);
    double current_gscore = gscores[current_index];

    if (current == goal_node) {
      std::vector<std::pair<int, int>> route;
      while (current_index != -1) {
        route.push_back(int2xy(current_index, map_size));
        current_index = camefrom[current_index];
      }
      std::reverse(route.begin(), route.end());
      //emit found_cost(current_gscore);
      emit found_goal(RetVal(current_gscore, route));
      return;
    }

    std::vector<Node> children_list;
    SearchTools::children(current, citymap, children_list);

    for (auto child: children_list) {
      double tentative_gscore = current_gscore + child.cost;
      int child_index = xy2int(child, map_size);

      emit visit_node(child.x, child.y);
      
      if (gscores.find(child_index) == gscores.end() || tentative_gscore < gscores[child_index]) {
        gscores[child_index] = tentative_gscore;
        camefrom[child_index] = current_index;
        child.cost = tentative_gscore + SearchTools::heuristics(child, goal_node);
        heap.push(child);
      }
    }
  }
  //emit found_cost(-1.0);
  emit found_goal(RetVal());
  return;
}
