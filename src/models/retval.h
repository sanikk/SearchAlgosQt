#pragma  once
#include <vector>
#include <sstream> 
#include <optional>
#include <chrono>

/// Simple Return Value struct. Returned from Searches.
struct RetVal {
  RetVal(bool i_found=false) : found(i_found), route(std::vector<std::pair<int, int>>()) {}
  RetVal(double i_cost, std::vector<std::pair<int, int>> i_route) : found(true), cost(i_cost), route(i_route) {}

  bool found;
  std::optional<double> cost;
  std::optional<std::chrono::duration<double>> timing;
  std::vector<std::pair<int, int>> route;

  // TODO: dev stuff, remove this
  friend std::string operator<<(std::ostream& os, const RetVal& obj) {
    std::ostringstream oss;
    oss << "Return value found:" << obj.found;
    if (obj.cost.has_value()) {
      oss << ", cost:" << obj.cost.value();
    }
    if (obj.timing.has_value()) {
      oss << ", timing:" << obj.timing.value().count();
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
