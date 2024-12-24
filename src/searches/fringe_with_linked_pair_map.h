#pragma once
#include "linked_pair_map.h"
#include "models.h"
#include "shared_search_tools.h"
#include "tools.h"

RetVal fringe_with_linked_pair_map(int startx, int starty, int goalx, int goaly, std::vector<std::string> citymap);
