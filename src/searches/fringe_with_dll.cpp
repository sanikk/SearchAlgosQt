#include "fringe_with_dll.h"
#include <iostream>


RetVal fringe_with_dll(int startx, int starty, int goalx, int goaly, std::vector<std::string> citymap) {
  const int map_size = citymap.size();
  const int start_index = xy2int(startx, starty, map_size);
  const int goal_index = xy2int(goalx, goaly, map_size);

  Fringe fringe(start_index);

  //                                parent, cost_here
  std::unordered_map<int, std::tuple<int, double>> cache;
  cache[start_index] = {-1, 0.0};
  bool found = false;
  double foundcost;
  double flimit = float_adjust(heuristics(startx, starty, goalx, goaly));

  std::vector<std::tuple<int, int, double>> kids;

  while (!found && !fringe.empty()) {
    double fscore_min = 1000000;
    for(const int current: fringe) {
      const auto [nx, ny] = int2xy(current, map_size);
      const auto [parent, gscore] = cache[current];

      const double fscore = gscore + heuristics(nx, ny, goalx, goaly);

      if (fscore > flimit) {
        fscore_min = std::min(fscore_min, fscore);
        continue;
      }

      if (current == goal_index) {
        std::cout << "goal found with cost " << gscore << std::endl;
        found = true;
        foundcost = gscore;
        break;
      }
      children(nx, ny, citymap, kids);
      for(const auto [childx, childy, childcost]: kids) {
        const double child_gscore = gscore + childcost;
        const int child_index = xy2int(childx, childy, map_size);

        if (cache.find(child_index)!=cache.end()) {
          const auto [cached_parent, cached_gscore] = cache[child_index];
          if (child_gscore >= cached_gscore) {
            continue;
          }
        }
        fringe.add(child_index);
        cache[child_index] = {current, child_gscore};
      }
      kids.clear();
      fringe.remove(current);
    }
    flimit = float_adjust(fscore_min);
  }
if (found) {
    std::vector<std::pair<int,int>> route;
    int current = goal_index;
    while (current != -1) {
      auto [cx, cy] = int2xy(current, map_size);
      route.push_back({cx,cy});
      current = std::get<0>(cache[current]);
    }
    return RetVal(foundcost, route);
  }
  return RetVal();
}
