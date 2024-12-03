#pragma once
#include "node.h"
#include <array>
#include <string>
#include <vector>
#include <cmath>

const double DIAG = std::sqrt(2.0);

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
