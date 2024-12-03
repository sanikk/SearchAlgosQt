#pragma once
#include <functional>

struct Node {
  double cost;
  int x, y;

  Node(int i_x, int i_y, double i_cost) : x(i_x), y(i_y), cost(i_cost) {}
  Node(int i_x, int i_y) : x(i_x), y(i_y) {}
  Node() {}

  friend bool operator==(const Node& l, const Node& r) { return l.x==r.x && l.y == r.y; }
  friend bool operator<(const Node& l, const Node& r) { return l.cost < r.cost; }
  friend bool operator>(const Node& l, const Node& r) { return l.cost > r.cost; }
};

struct NodeHash {
  std::size_t operator()(const Node& node) const {
      return std::hash<int>()(node.x) ^ (std::hash<int>()(node.y) << 1);
  }
};
