#pragma  once
#include <vector>
#include <sstream> 
#include <optional>

struct RetVal {
  bool found;
  std::optional<double> cost;
  std::optional<double> timing;
  std::vector<std::pair<int, int>> route;

  RetVal(bool i_found=false) : found(i_found), route(std::vector<std::pair<int, int>>()) {}
  // RetVal(double i_cost, std::vector<int> i_route, int map_size) : found(true), cost(i_cost), route(pair_route(i_route, map_size)) {}
  RetVal(double i_cost, std::vector<std::pair<int, int>> i_route) : found(true), cost(i_cost), route(i_route) {}


  friend std::string operator<<(std::ostream& os, const RetVal& obj) {
    std::ostringstream oss;
    oss << "Return value found:" << obj.found;
    if (obj.cost.has_value()) {
      oss << ", cost:" << obj.cost.value();
    }
    if (obj.timing.has_value()) {
      oss << ", timing:" << obj.timing.value();
    }
    if (!obj.route.empty()) {
      oss << "\nRoute: ";
    }
    
    for (auto node : obj.route) {
      oss << "(" << node.first << "," << node.second << "), ";
    }
    oss << std::endl;
    return oss.str();
  }
};
