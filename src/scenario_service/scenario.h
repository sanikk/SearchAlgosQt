#pragma once

#include <ostream>
struct Scenario {
  int id;
  int start_x;
  int start_y;
  int goal_x;
  int goal_y;
  float cost;


  friend std::ostream& operator<<(std::ostream& os, const Scenario& obj) {
    return os << "Scenario id:" << obj.id << ", start(" << obj.start_x << "," << obj.start_y << "), goal(" << obj.goal_x << "," << obj.goal_y << "), cost: " << obj.cost << std::endl; 
  }
};
