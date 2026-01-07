#include "astar_with_signals.h"
#include "shared_search_tools.h"

#include <queue>
#include <unordered_map>

RetVal astar_with_signals(int startx, 
                    int starty, 
                    int goalx, 
                    int goaly, 
                    const std::vector<std::string> &citymap,
                    SearchSignals* signals_pack
                    ) {

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
    signals_pack->node_expanded(current.x, current.y);
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
      return RetVal(current_gscore, pair_route(route, map_size));
    }

    std::vector<Node> children_list;
    children(current, citymap, children_list);

    for (auto child: children_list) {
      signals_pack->node_visited(child.x, child.y);

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
  return RetVal();
}
