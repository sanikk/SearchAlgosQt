#pragma once
#include "models.h"
#include "tools.h"
#include "shared_search_tools.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>



RetVal fringe_search(int startx, int starty, int goalx, int goaly, std::vector<std::string> citymap); 
