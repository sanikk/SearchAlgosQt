#pragma  once
#include "tools.h"
#include <vector>


struct RetVal {
  bool found;
  double cost;
  std::vector<std::pair<int, int>> route;

  RetVal(bool i_found=false) : found(i_found) {}
  RetVal(double i_cost, std::vector<int> i_route, int map_size) : found(true), cost(i_cost), route(pair_route(i_route, map_size)) {}
  RetVal(double i_cost, std::vector<std::pair<int, int>> i_route) : found(true), cost(i_cost), route(i_route) {}
};
