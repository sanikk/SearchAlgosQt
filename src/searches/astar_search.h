#pragma once
#include "retval.h"
#include <vector>
#include <string>

RetVal astar_search(int startx, int starty, int goalx, int goaly, int width, int height, const std::vector<std::string>& citymap);
RetVal astar_search(int startx, int starty, int goalx, int goaly, int width, int height, const std::vector<uint8_t>& citymap);
