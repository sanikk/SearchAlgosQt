#include "astar_thread.h"

#include "children.h"
#include "heuristics.h"

#include <queue>
#include <unordered_map>

#include <iostream>

AstarThread::AstarThread(int startx, int starty, int goalx, int goaly, const std::vector<std::string>& citymap, SearchService* search_service) 
: SearchThread(startx, starty, goalx, goaly, citymap)
{
  QObject::connect(this, &SearchThread::visit, search_service, &SearchService::astarVisit);
  QObject::connect(this, &SearchThread::expand, search_service, &SearchService::astarExpand);
}

void AstarThread::run() {
  // std::cout << "AstarThread run " << QThread::currentThread() << std::endl;
  // astar_with_signals(startx, starty, goalx, goaly, citymap);
  astar_search_thread(startx, starty, goalx, goaly, citymap);
}

void AstarThread::astar_with_signals(const int startx, 
                    const int starty, 
                    const int goalx, 
                    const int goaly, 
                    const std::vector<std::string> &citymap
                    //, SearchSignals* signals_pack
                    ) {
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
    //signals_pack->node_expanded(current.x, current.y);
    expand(current.x, current.y);
    std::cout << "popped " << current.x << "," << current.y << std::endl;
    heap.pop();
    
    int current_index = xy2int(current, map_size);
    double current_gscore = gscores[current_index];

    if (current == goal_node) {
      std::vector<int> route;
      while (current_index != -1) {
        route.push_back(current_index);
        current_index = camefrom[current_index];
      }
      std::reverse(route.begin(), route.end());
      // signals_pack->search_finished(RetVal(current_gscore, pair_route(route, map_size)));
      std::cout << "search finished with cost " << current_gscore << std::endl;
      return;
    }

    std::vector<Node> children_list;
    SearchTools::children(current, citymap, children_list);
    std::cout << "returned " << children_list.size() << " children" << std::endl;

    for (auto child: children_list) {
      //signals_pack->node_visited(child.x, child.y);
      visit(child.x, child.y);
      std::cout << "child " << child.x << "," << child.y << std::endl;

      double tentative_gscore = current_gscore + child.cost;
      int child_index = xy2int(child, map_size);
      
      if (gscores.find(child_index) == gscores.end() || tentative_gscore < gscores[child_index]) { 
        gscores[child_index] = tentative_gscore;
        camefrom[child_index] = current_index;
        child.cost = tentative_gscore + SearchTools::heuristics(child, goal_node);
        heap.push(child);
        std::cout << "pushed" << std::endl;
      } else {
        std::cout << "dropped" << std::endl;
      }
    }
  }
  std::cout << "search failed" << std::endl;
  //signals_pack->search_finished(RetVal());
}


void AstarThread::astar_search_thread(int startx, int starty, int goalx, int goaly, const std::vector<std::string> &citymap) {

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

    // std::cout << "popped " << current.x << "," << current.y << std::endl;

    emit expand(current.x, current.y);
    
    int current_index = xy2int(current, map_size);
    double current_gscore = gscores[current_index];
    // std::cout << "current gscore " << current_gscore << std::endl;

    // std::cout << "current is " << current.x << "," << current.y << " with estimated cost: " << current.cost << "and gscores "<< current_gscore << std::endl;

    if (current == goal_node) {
      // std::cout << "goal found with cost " << current_gscore << std::endl;
      std::vector<int> route;
      while (current_index != -1) {
        route.push_back(current_index);
        current_index = camefrom[current_index];
      }
      std::reverse(route.begin(), route.end());
      return;
      //return RetVal(current_gscore, pair_route(route, map_size));
    }

    std::vector<Node> children_list;
    SearchTools::children(current, citymap, children_list);

    for (auto child: children_list) {
      emit visit(child.x, child.y);
      // std::cout << "child " << child.x << "," << child.y << "with cost " << child.cost << std::endl;
      double tentative_gscore = current_gscore + child.cost;
      int child_index = xy2int(child, map_size);
      
      if (gscores.find(child_index) == gscores.end() || tentative_gscore < gscores[child_index]) {
        
      
        gscores[child_index] = tentative_gscore;
        camefrom[child_index] = current_index;
        child.cost = tentative_gscore + SearchTools::heuristics(child, goal_node);
        heap.push(child);
      }
    }
  }
  // std::cout << "not found" << std::endl;
  return;
  //return RetVal();
}
