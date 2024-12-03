#include "fringe_search.h"
#include <iostream>

template<typename M, typename K, typename... Args>
void emplaced(M& map, K&& key, Args&&... args) {
  map.emplace(std::piecewise_construct,
    std::forward_as_tuple(std::forward<K>(key)),
    std::forward_as_tuple(std::forward<Args>(args)...)
  );
}

 std::tuple<double, std::optional<std::vector<std::pair<int, int>>>> fringe_search(int startx, int starty, int goalx, int goaly, const std::vector<std::string>& citymap) {
  // TODO: at least scenarios 1336, 1337, 162 give wrong answers. mabbe visualize?
  int map_size = citymap.size();

  const double EPSILON = 0.00001;
  
  int start = starty * map_size + startx;
  int goal = goaly * map_size + goalx;

  std::deque<int> now = {start};
  std::deque<int> later;

  double start_f = heuristics(startx, starty, goalx, goaly);
  // std::cout << "flimit " << flimit << std::endl;
  bool found = false;

  // parent, cost_here, f_score
  std::unordered_map<int, std::tuple<int, double, double>> cache;
  std::vector<std::tuple<int, int, double>> children_list;
  emplaced(cache, start, -1, 0.0, start_f);
  double flimit = start_f + EPSILON;
  while (!found) {
    double fmin = std::numeric_limits<double>::max();
    while (!now.empty() && not found) {
      int current = now.back();
      now.pop_back();
    
      std::tuple<int, double, double> data = cache[current];
      int ny = current / map_size; 
      int nx = current % map_size;

      if (std::get<2>(data) == -1) {
        data = {std::get<0>(data), std::get<1>(data), std::get<1>(data) + heuristics(nx, ny, goalx, goaly)};
        cache[current] = data;
      }

      if (std::get<2>(data) > flimit) {
        fmin = std::min(std::get<2>(data), fmin);
        if (std::find(later.begin(), later.end(), current) == later.end()) {
          later.push_back(current);
          }
        continue;
      }

      if (current == goal) {
        found = true;
        std::cout << "found with cost " << std::get<1>(data) << std::endl;
        // Reconstruct route
        std::pair<int, int> here = {nx, ny};
        std::vector<std::pair<int, int>> route = {{nx, ny}};
        while (current != start) {
          current = std::get<0>(cache[current]);
          ny = current / map_size;
          nx = current % map_size;
          route.push_back({nx, ny});
        }
        // std::reverse(route.begin(), route.end());
        return {std::get<1>(data), route};
      }
      children(nx, ny, citymap, children_list);
      for (const auto& [cx, cy, cc] : children_list) {
        int child_index = cy * map_size + cx;
        double g_child = std::get<1>(data) + cc;
        auto res = cache.find(child_index);
        if (res != cache.end() && std::get<1>(res->second) < g_child) {
          continue;
        }
        emplaced(cache, child_index, current, g_child, -1);
        now.push_back(child_index);
      }
      children_list.clear();
    }
    if (!found) {
      if (later.empty()) {
        return {-1.0, std::nullopt};
      }
      std::swap(now, later);
      flimit = fmin + EPSILON;
      std::cout << "flimit set to " << flimit << std::endl;
    }
  }
  return {-1.0, std::nullopt};

}
