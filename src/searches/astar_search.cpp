#include "astar_search.h"

#include "conversions.h"
#include "node.h"
#include "children.h"
#include "heuristics.h"

#include <queue>
#include <unordered_map>
#include <algorithm>


void reconstruct_route() {
}


RetVal astar_search(int startx, int starty, int goalx, int goaly, int width, int height, const std::vector<std::string> &citymap) {

  Node start_node{startx, starty, starty*width + startx};
  Node goal_node{goalx, goaly, goaly * width + goalx};
  start_node.cost = SearchTools::heuristics(start_node, goal_node);

  std::priority_queue<Node, std::vector<Node>, std::greater<Node>> heap;
  heap.push(start_node);
  
  std::unordered_map<int, double> gscores;
  gscores[start_node.index] = 0.0;
  std::unordered_map<int, int> camefrom;
  camefrom[start_node.index] = -1;

  while (!heap.empty()) {
    Node current_node = heap.top();
    heap.pop();
    
    double current_gscore = gscores[current_node.index];


    if (current_node.index == goal_node.index) {
      std::vector<int> route;
      int current_index = current_node.index;
      while (current_index != -1) {
        route.push_back(current_index);
        current_index = camefrom[current_index];
      }
      std::reverse(route.begin(), route.end());
      return RetVal(current_gscore, pair_route(route, width));
    }

    std::vector<Node> children_list;
    SearchTools::children(current_node, citymap, children_list);

    for (auto child: children_list) {
      double tentative_gscore = current_gscore + child.cost;
      
      if (gscores.find(child.index) == gscores.end() || tentative_gscore < gscores[child.index]) { 
        gscores[child.index] = tentative_gscore;
        camefrom[child.index] = current_node.index;
        child.cost = tentative_gscore + SearchTools::heuristics(child, goal_node);
        heap.push(child);
      }
    }
  }
  return RetVal();
}

RetVal astar_search(int startx, int starty, int goalx, int goaly, int width, int heigth, const std::vector<uint8_t> &citymap) {
  ChildrenNodes children = ChildrenNodes(width, heigth, citymap);

  Node start_node{startx, starty, starty * width + startx};
  Node goal_node{goalx, goaly, goaly * width + goalx};
  start_node.cost = SearchTools::heuristics(start_node, goal_node);

  std::priority_queue<Node, std::vector<Node>, std::greater<Node>> heap;
  heap.push(start_node);
  
  std::unordered_map<int, double> gscores;
  gscores[start_node.index] = 0.0;
  std::unordered_map<int, int> camefrom;
  camefrom[start_node.index] = -1;

  while (!heap.empty()) {
    Node current_node = heap.top();
    heap.pop();
    
    double current_gscore = gscores[current_node.index];


    if (current_node.index== goal_node.index) {
      std::vector<int> route;
      int current_index = current_node.index;
      while (current_index != -1) {
        route.push_back(current_node.index);
        current_index = camefrom[current_index];
      }
      std::reverse(route.begin(), route.end());
      return RetVal(current_gscore, pair_route(route, width));
    }

    std::vector<Node> children_list = children.get_nodes(current_node);

    for (auto child: children_list) {
      double tentative_gscore = current_gscore + child.cost;
      
      if (gscores.find(child.index) == gscores.end() || tentative_gscore < gscores[child.index]) {
        gscores[child.index] = tentative_gscore;
        camefrom[child.index] = current_node.index;
        child.cost = tentative_gscore + SearchTools::heuristics(child, goal_node);
        heap.push(child);
      }
    }
  }
  return RetVal();
}
