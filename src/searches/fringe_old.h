#include "common/heuristics.h"
#include "common/children.h"
#include <queue>
#include <string>
#include <vector>
#include <optional>
#include <algorithm>

 
std::tuple<double, std::optional<std::vector<std::pair<int, int>>>> fringe_search(int startx, \
                int starty, int goalx, int goaly, const std::vector<std::string>& citymap); 
