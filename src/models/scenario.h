#pragma once
#include <ostream>

/// Simple struct to hold and pass single Scenario data
struct Scenario {
  int id;
  int bucket;
  int start_x;
  int start_y;
  int goal_x;
  int goal_y;
  double cost;

  // TODO: dev stuff, remove this
  friend std::ostream& operator<<(std::ostream& os, const Scenario& obj) {
    return os << "Scenario id:" << obj.id << ", start(" << obj.start_x << "," << obj.start_y << "), goal(" << obj.goal_x << "," << obj.goal_y << "), cost: " << obj.cost << std::endl; 
  }
};
