#include "fringe_unopt.h"
#include <iomanip>
#include <iostream>

int xy2int(int x, int y, int map_size) {
  return y*map_size + x;
}

std::pair<int, int> int2xy(int index, int map_size) {
  int x = index % map_size;
  int y = index / map_size;
  return std::make_pair(x,y);
}

double fringe_search_unopt(int startx, int starty, int goalx, int goaly, std::vector<std::string> citymap) {

    // Invoking Knuth
    // Premature optimization is the root of all evil.

    // INIT
    int map_size = citymap.size();
    int start_index = xy2int(startx, starty, map_size);
    int goal_index = xy2int(goalx, goaly, map_size);
    std::deque<int> now = {start_index};
    std::deque<int> later = {};
    
    std::unordered_map<int, std::tuple<double, int>> cache;
    //                              cost_here, parent
    cache[xy2int(startx, starty, map_size)] = {0.0, -1};
      
    bool found = false;
    double epsilon = 0.00000002;
    double flimit = heuristics(startx, starty, goalx, goaly) + epsilon;

    // std::cout << "initial flimit " << std::setprecision(17) << flimit << std::endl;


    while (!found && !now.empty()) 
    {
        double fscore_min = 100000;

        while(!now.empty()) 
            
        {
            int current = now.back();
            now.pop_back();
            const auto [g_score, parent] = cache[current];
            const auto[nx, ny] = int2xy(current, map_size);

            // std::cout << nx << "," << ny << std::endl;

            double fscore = g_score + heuristics(nx, ny, goalx, goaly);

            if (fscore > flimit) {
                fscore_min = std::min(fscore, fscore_min);
                later.push_back(current);
                continue;
            }

            if (current == goal_index) {
                std::cout << std::setprecision(10) << "found goal! cost " << g_score << std::endl;
                found = true;
                break;
            }

            std::vector<std::tuple<int, int, double>> succ_list;
            children(nx, ny, citymap, succ_list);
            for (const auto [succ_x, succ_y, succ_cost] : succ_list) {

                double succ_gscore = g_score + succ_cost;
                int succ_index = xy2int(succ_x, succ_y, map_size);

                // ::cout << "kid "<< succ_x << "," << succ_y << std::endl;

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
        if (!found) {
            if (!later.empty()) {
                flimit = fscore_min + epsilon;
                // std::cout << "flimit set to " << std::setprecision(17) << flimit << std::endl;
                std::swap(later, now);
            } else {
                std::cout << "not found" << std::endl;
                return -1.0;
            }
        }
    }
  
    std::cout << "not found" << std::endl;
    return -1.0;

}
