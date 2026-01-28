#pragma once
#include "node.h"
#include <array>
#include <string>
#include <vector>
#include <cmath>

const double DIAG = std::sqrt(2.0);

namespace SearchTools {
  


const std::array<std::tuple<int, int, double>, 8> neighbor_offsets = {{
  { 0, -1, 1.0 },   // Up
  {-1, -1, DIAG}, // Up-Left
  {-1,  0, 1.0 },   // Left
  {-1,  1, DIAG}, // Down-Left
  { 0,  1, 1.0 },   // Down
  { 1,  1, DIAG}, // Down-Right
  { 1,  0, 1.0 },   // Right
  { 1, -1, DIAG},  // Up-Right
}};

void children(int x, int y, const std::vector<std::string>& citymap, std::vector<Node>& node_list);
void children(int x, int y, const std::vector<std::string>& citymap, std::vector<std::tuple<int, int, double>>& node_list);
void children(Node node, const std::vector<std::string>& citymap, std::vector<Node>& node_list);

}

struct Offset {
  int delta;
  double cost;

  Offset(int delta, double cost) : delta(delta), cost(cost) {};
};

struct NodeOffset {
  int index_delta, x_delta, y_delta;
  double cost;
  NodeOffset(int index_delta, int x_delta, int y_delta, double cost) 
  : index_delta(index_delta), x_delta(x_delta), y_delta(y_delta), cost(cost) {};
};

class Children {

public:
  explicit Children(const int width, const int heigth, const std::vector<uint8_t>& citymap) : width_(width), heigth_(heigth), citymap_(&citymap) {}

protected:
  const int width_;
  const int heigth_;
  const std::vector<uint8_t>* citymap_;
};


class ChildrenTuples : public Children {
public:
  explicit ChildrenTuples(const int width, const int height, const std::vector<uint8_t>& citymap);
  void children(int current_index);
  void children(int x, int y);
  std::vector<std::tuple<int, int, int, double>>& get_tuples(int x, int y);
  std::vector<std::tuple<int, int, int, double>>& get_tuples(int current_index);
private:
  const std::array<NodeOffset, 8> offsets_;
  std::vector<std::tuple<int, int, int, double>> out_tuples_;

};


class ChildrenNodes : public Children {
public:
  explicit ChildrenNodes(const int width, const int height, const std::vector<uint8_t>& citymap);
  void children(Node node);
  std::vector<Node>& get_nodes(Node current);
private:
  const std::array<NodeOffset, 8> offsets_;
  std::vector<Node> out_nodes_;
};
