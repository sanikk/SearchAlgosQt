#include "tools.h"

int xy2int(int x, int y, int map_size) {
  return y*map_size + x;
}

int xy2int(std::pair<int, int> pari, int map_size) {
  return xy2int(pari.first, pari.second, map_size);
}

int xy2int(Node node, int map_size) {
  return node.y * map_size + node.x;
}

std::pair<int, int> int2xy(int index, int map_size) {
  int x = index % map_size;
  int y = index / map_size;
  return std::make_pair(x,y);
}


std::vector<std::pair<int, int>> pair_route(std::vector<int> route, int map_size) {
  std::vector<std::pair<int, int>> returnable;
  for (int index : route) {
    returnable.push_back(int2xy(index, map_size));
  }
  return returnable;
}


std::vector<int> unpair_route(std::vector<std::pair<int, int>> route, int map_size){
  std::vector<int> returnable;
  for (auto pari : route) {
    returnable.push_back(xy2int(pari, map_size));
  }
  return returnable;
}
