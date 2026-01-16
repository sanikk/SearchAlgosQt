#include "worker.h"

#include "children.h"
#include "heuristics.h"
#include "conversions.h"

#include <queue>

#include <QThread>
//#include <QDebug>


WorkerRunner::WorkerRunner() {}


void WorkerRunner::run_astar(int startx, int starty, int goalx, int goaly, 
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
  connect(worker, &AstarWorker::found_goal, search_service, &SearchService::astarFound, Qt::QueuedConnection);

  thread->start();
}

void WorkerRunner::run_fringe(int startx, int starty, int goalx, int goaly, 
                              const std::vector<std::string>& citymap, 
                              SearchService* search_service) {

  QThread* thread = new QThread;
  FringeWorker* worker = new FringeWorker{startx, starty, goalx, goaly, citymap};
  worker->moveToThread(thread);

  connect(thread, &QThread::started, worker, &FringeWorker::run);
  connect(worker, &FringeWorker::finished, thread, &QThread::quit);
  connect(worker, &FringeWorker::finished, worker, &QObject::deleteLater);
  connect(thread, &QThread::finished, thread, &QObject::deleteLater);
  
  connect(worker, &FringeWorker::visit_node, search_service, &SearchService::fringeVisit, Qt::QueuedConnection);
  connect(worker, &FringeWorker::expand_node, search_service, &SearchService::fringeExpand, Qt::QueuedConnection);
  connect(worker, &FringeWorker::found_goal, search_service, &SearchService::fringeFound, Qt::QueuedConnection);

  thread->start();
}



// WORKER

Worker::Worker(int startx, int starty, int goalx, int goaly, 
               const std::vector<std::string>& i_citymap)
: startx(startx), starty(starty), goalx(goalx), goaly(goaly), citymap(i_citymap) {
}




// A*


AstarWorker::AstarWorker(int startx, int starty, int goalx, int goaly, 
                         const std::vector<std::string>& i_citymap)
: Worker(startx, starty, goalx, goaly, i_citymap) {
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
  emit found_goal(RetVal());
  return;
}


// FRINGE

FringeWorker::FringeWorker(int startx, int starty, int goalx, int goaly, 
                           const std::vector<std::string>& i_citymap)
: Worker(startx, starty, goalx, goaly, i_citymap) {
}

void FringeWorker::run() {
  fringe_with_signals();
  emit finished();
}

void FringeWorker::fringe_with_signals() {
    // INIT
    int map_size = citymap.size();
    int start_index = xy2int(startx, starty, map_size);
    int goal_index = xy2int(goalx, goaly, map_size);
    std::deque<int> now = {start_index};
    std::deque<int> later = {};
    
    std::unordered_map<int, std::tuple<double, int>> cache;
    //                                   cost_here, parent
    cache[xy2int(startx, starty, map_size)] = {0.0, -1};
      
    bool found = false;
    double epsilon = 0.00000002;
    double flimit = SearchTools::heuristics(startx, starty, goalx, goaly) + epsilon;
    //qDebug() << "initial flimit " << flimit;

    while (true) 
    {
        double fscore_min = 100000;

        while(!now.empty()) 
            
        {
            int current = now.back();
            now.pop_back();
            const auto [g_score, parent] = cache[current];
            const auto[nx, ny] = int2xy(current, map_size);

            emit expand_node(nx, ny);
            // qDebug() << "expand " << nx << "," << ny;

            double fscore = g_score + SearchTools::heuristics(nx, ny, goalx, goaly);

            if (fscore > flimit) {
                fscore_min = std::min(fscore, fscore_min);
                later.push_back(current);
                continue;
            }

            if (current == goal_index) {
                //qDebug() << "found goal with cost " << g_score;
                found = true;
                std::vector<int> route;
                while (current != -1) {
                    route.push_back(current);
                    current = std::get<1>(cache[current]);
                }
                emit found_goal(RetVal(g_score, pair_route(route, map_size)));
                return;
            }

            std::vector<std::tuple<int, int, double>> succ_list;
            SearchTools::children(nx, ny, citymap, succ_list);
            for (const auto [succ_x, succ_y, succ_cost] : succ_list) {
                emit visit_node(succ_x, succ_y) ;
                double succ_gscore = g_score + succ_cost;
                int succ_index = xy2int(succ_x, succ_y, map_size);
                //qDebug() << "visit " << succ_x << "," << succ_y;

                if (cache.find(succ_index) != cache.end()) {
                    const auto[succ_gcache, cache_parent] = cache[succ_index];
                    if (succ_gscore >= succ_gcache) {
                      continue;
                    };
                };
                now.push_back(succ_index);
                cache[succ_index] = std::make_pair(succ_gscore, current);
            }; // for child
        } // while current
        if (!later.empty()) {
            flimit = fscore_min + epsilon;
            // qDebug() << "flimit set to " << flimit;
            std::swap(later, now);
        } else {
            emit found_goal(RetVal());
            // qDebug() << "first not found";
            return;
        }

    }
    emit found_goal(RetVal());
    // qDebug() << "second not found";
}
