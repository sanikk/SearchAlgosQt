#pragma once
#include "models.h"
#include "tools.h"
#include "shared_search_tools.h"
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <algorithm>

RetVal astar_search(int startx, int starty, int goalx, int goaly, const std::vector<std::string>& citymap);
