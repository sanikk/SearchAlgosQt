#pragma once
#include "models.h"
#include "tools.h"
#include <vector>
#include <string>

RetVal astar_with_signals(
    int startx, 
    int starty, 
    int goalx, 
    int goaly, 
    const std::vector<std::string>& citymap,
    SearchSignals* signals_pack
);


