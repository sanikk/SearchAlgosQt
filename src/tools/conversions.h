#pragma once
#include "node.h"
#include <vector>

// TODO: move conversions to search_tools, or all search_tools here.
// these can all stay in one dir. here in 'tools' might be better.

// x,y to a single int
int xy2int(int x, int y, int map_size);
int xy2int(Node node, int map_size);
std::pair<int, int> int2xy(int index, int map_size);

std::vector<std::pair<int, int>> pair_route(std::vector<int> route, int map_size);
std::vector<int> unpair_route(std::vector<std::pair<int, int>> route, int map_size);
