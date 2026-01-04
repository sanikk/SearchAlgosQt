#pragma once
#include "models.h"
#include <vector>
#include <string>

RetVal astar_search(int startx, int starty, int goalx, int goaly, const std::vector<std::string>& citymap);
