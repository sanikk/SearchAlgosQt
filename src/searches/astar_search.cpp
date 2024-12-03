#include "astar_search.h"
#include <iostream>


void reconstruct_route() {
}


RetVal astar_search(int startx, int starty, int goalx, int goaly, const std::vector<std::string> &citymap) {

  Node start_node{startx, starty};
  Node goal_node{goalx, goaly};
  start_node.cost = heuristics(start_node, goal_node);

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
    
    int current_index = xy2int(current, map_size);
    double current_gscore = gscores[current_index];
    // std::cout << "current gscore " << current_gscore << std::endl;

    // std::cout << "current is " << current.x << "," << current.y << " with estimated cost: " << current.cost << "and gscores "<< current_gscore << std::endl;

    if (current == goal_node) {
      std::cout << "goal found with cost " << current_gscore << std::endl;
      std::vector<int> route;
      while (current_index != -1) {
        route.push_back(current_index);
        current_index = camefrom[current_index];
      }
      std::reverse(route.begin(), route.end());
      return RetVal(current_gscore, route, map_size);
    }

    std::vector<Node> children_list;
    children(current, citymap, children_list);

    for (auto child: children_list) {
      // std::cout << "child " << child.x << "," << child.y << "with cost " << child.cost << std::endl;
      double tentative_gscore = current_gscore + child.cost;
      int child_index = xy2int(child, map_size);
      
      if (gscores.find(child_index) == gscores.end() || tentative_gscore < gscores[child_index]) {
        
      
        gscores[child_index] = tentative_gscore;
        camefrom[child_index] = current_index;
        child.cost = tentative_gscore + heuristics(child, goal_node);
        heap.push(child);
      }
    }
  }
  std::cout << "not found" << std::endl;
  return RetVal();
}
