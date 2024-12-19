#include "fringe_with_linked_map_pairs.h"
#include <iostream>

RetVal fringe_with_linked_map_pairs(int startx, int starty, int goalx,
                                    int goaly,
                                    std::vector<std::string> citymap) {
  const int map_size = citymap.size();
  const int start_index = xy2int(startx, starty, map_size);
  const int goal_index = xy2int(goalx, goaly, map_size);

  LinkedMapPairs fringe(start_index, map_size);

  //                                parent, cost_here
  std::unordered_map<int, std::tuple<int, double>> cache;
  cache[start_index] = {-1, 0.0};
  bool found = false;
  double foundcost;
  double flimit = float_adjust(heuristics(startx, starty, goalx, goaly));

  std::vector<std::tuple<int, int, double>> kids;

  while (!found && fringe.head != fringe.end) {
    double fscore_min = 1000000;
    std::unordered_map<int, LinkNode *>::iterator fringe_it = fringe.head;
    while (fringe_it != fringe.end) {
      int current = fringe_it->first;
      const auto [nx, ny] = int2xy(current, map_size);
      const auto [parent, gscore] = cache[current];

      const double fscore = gscore + heuristics(nx, ny, goalx, goaly);

      // std::cout << "current: " << current << ", (" << nx << "," << ny
      //           << "):" << gscore << std::endl;
      if (fscore > flimit) {
        fringe_it = fringe_it->second->right;
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
      for (const auto [childx, childy, childcost] : kids) {
        // std::cout << "child " <<childx << "," << childy << ":" << childcost
        // << std::endl;
        const double child_gscore = gscore + childcost;
        const int child_index = xy2int(childx, childy, map_size);

        if (cache.find(child_index) != cache.end()) {
          const auto [cached_parent, cached_gscore] = cache[child_index];
          if (child_gscore >= cached_gscore) {
            continue;
          }
        }
        fringe.add_tail(child_index);
        cache[child_index] = {current, child_gscore};
      } // for the children
      kids.clear();
      fringe.remove_current(fringe_it);
    } // for current : fringe
    flimit = float_adjust(fscore_min);
  } // while not found
  if (found) {
    std::vector<std::pair<int, int>> route;
    int current = goal_index;
    while (current != -1) {
      auto [cx, cy] = int2xy(current, map_size);
      route.push_back({cx, cy});
      // std::cout << cx << "," << cy << std::endl;
      current = std::get<0>(cache[current]);
    }
    return RetVal(foundcost, route);
  }
  return RetVal();
}
