#pragma once
#include "common/searches_common.h"
#include <vector>
#include <string>
#include <queue>

int get_one();

RetVal astar_search(int startx, int starty, int goalx, int goaly, const std::vector<std::string> &citymap);

