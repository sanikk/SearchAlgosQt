#include "fringe_search.h"
#include <iomanip>
#include <iostream>


RetVal fringe_search(int startx, int starty, int goalx, int goaly, std::vector<std::string> citymap) {

    // Invoking Knuth
    // Premature optimization is the root of all evil.

    // INIT
    int map_size = citymap.size();
    int start_index = xy2int(startx, starty, map_size);
    int goal_index = xy2int(goalx, goaly, map_size);
    std::deque<int> now = {start_index};
    std::deque<int> later = {};
    
    // std::unordered_map<int, std::tuple<double, int>> cache;
    //                              cost_here, parent
    //                              cost here, hscore, parent
    //
    double epsilon = 0.00000002;

    double hscore;
    hscore = heuristics(startx, starty, goalx, goaly);
    double flimit = hscore + epsilon;
    
    std::unordered_map<int, std::tuple<double, double, int>> cache;
    cache[xy2int(startx, starty, map_size)] = {0.0, hscore, -1};
      
    bool found = false;
    double gscore;
    int parent;

    // std::cout << "initial flimit " << std::setprecision(17) << flimit << std::endl;


    while (true) 
    {
        double fscore_min = 100000;

        while(!now.empty()) 
            
        {
            int current = now.back();
            now.pop_back();
            const auto [g_score, hscore, parent] = cache[current];
            const auto[nx, ny] = int2xy(current, map_size);

            // std::cout << nx << "," << ny << std::endl;
            if (hscore == -1) {
                hscore = heuristics(nx, ny, goalx, goaly);
                cache[current] = {g_score, hscore, parent};
            }
            double fscore = g_score + hscore;

            if (fscore > flimit) {
                fscore_min = std::min(fscore, fscore_min);
                later.push_back(current);
                continue;
            }

            if (current == goal_index) {
                std::cout << std::setprecision(10) << "found goal! cost " << g_score << std::endl;
                found = true;
                std::vector<int> route;
                while (current != -1) {
                    route.push_back(current);
                    current = std::get<2>(cache[current]);
                }
                return RetVal(g_score, pair_route(route, map_size));
                // break;
            }

            std::vector<std::tuple<int, int, double>> succ_list;
            children(nx, ny, citymap, succ_list);
            for (const auto [succ_x, succ_y, succ_cost] : succ_list) {

                double succ_gscore = g_score + succ_cost;
                int succ_index = xy2int(succ_x, succ_y, map_size);

                // ::cout << "kid "<< succ_x << "," << succ_y << std::endl;

                if (cache.find(succ_index) != cache.end()) {
                    const auto[succ_gcache, hscore, cache_parent] = cache[succ_index];
                    if (succ_gscore >= succ_gcache) {
                      continue;
                    }
                } else {
                    hscore = -1};
                }
                now.push_back(succ_index);
                
                cache[succ_index] = {succ_gscore, hscore, current};
            }; // for child
        } // while current
        if (!later.empty()) {
            flimit = fscore_min + epsilon;
                // std::cout << "flimit set to " << std::setprecision(17) << flimit << std::endl;
            std::swap(later, now);
        } else {
            std::cout << "not found" << std::endl;
            return RetVal();
        }
        
    }
    // std::cout << "not found" << std::endl;
}
