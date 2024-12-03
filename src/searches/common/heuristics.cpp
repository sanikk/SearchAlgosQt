#include "heuristics.h"

double heuristics(int nodex, int nodey, int goalx, int goaly) {
  double abs_dx = abs(nodex - goalx);
  double abs_dy = abs(nodey - goaly);
  if (abs_dx < abs_dy)
    return static_cast<double>(abs_dx + abs_dy + DIFF * abs_dx);
  return static_cast<double>(abs_dx + abs_dy + DIFF * abs_dy);
}

double heuristics(Node node, Node goal) {
  return heuristics(node.x, node.y, goal.x, goal.y);
}
