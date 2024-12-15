#include "astar_search.h"
#include <iostream>


std::vector<std::pair<int, int>> reconstruct_route(std::unordered_map<int, int>& cameFrom, int current_index, const int& map_size) {
  std::vector<std::pair<int, int>> route;
  while (current_index != -1) {
    route.push_back(int2xy(current_index, map_size));
    current_index = cameFrom[current_index];
  }
  std::reverse(route.begin(), route.end());
  return route;
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

    if (current == goal_node) {
      std::cout << "goal found with cost " << current_gscore << std::endl;
      return RetVal(current_gscore, reconstruct_route(camefrom, current_index, map_size));
    }

    std::vector<Node> children_list;
    children(current, citymap, children_list);

    for (auto child: children_list) {
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
