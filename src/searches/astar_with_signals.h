#pragma once
#include "models.h"
#include "tools.h"
#include <vector>
#include <string>

void astar_with_signals(
    const int startx, 
    const int starty, 
    const int goalx, 
    const int goaly, 
    const std::vector<std::string>& citymap,
    SearchSignals* signals_pack
);


