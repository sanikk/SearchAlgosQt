#pragma once
#include <functional>

/// Simple struct to represent a single Node on the map.
struct Node {
  double cost;
  int x, y;
  /// (x,y) as a single int
  int index;

  Node(int i_x, int i_y, int i_index, int i_cost) 
    : x(i_x), y(i_y), index(i_index), cost(i_cost) {}
  Node(int i_x, int i_y, int i_index) : x(i_x), y(i_y), index(i_index) {}
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
