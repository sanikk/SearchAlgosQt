#include "common/searches_common.h"
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <algorithm>

RetVal astar_search(int startx, int starty, int goalx, int goaly, const std::vector<std::string>& citymap);
