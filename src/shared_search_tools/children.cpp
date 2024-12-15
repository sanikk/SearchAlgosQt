#include "children.h"

void children(int x, int y, const std::vector<std::string>& citymap, std::vector<Node>& node_list) {
  int map_size = citymap.size();
  for (int i=0;i < 8;i++) {
    const auto& [dx, dy, cost] = neighbor_offsets[i];
    int nx = x + dx;
    int ny = y + dy;
    if (nx < 0 || nx >= map_size || ny < 0 || ny >= map_size || citymap[ny][nx] != '.') {
      continue;
    }
    if (i % 2 == 0) {
      node_list.push_back(Node(nx, ny, cost));
    } else {
      int dx1 = x + std::get<0>(neighbor_offsets[i-1]);
      int dy1 = y + std::get<1>(neighbor_offsets[i-1]);
      if (dx1 < 0 || dx1 >= map_size || dy1 < 0 || dy1 >= map_size || citymap[dy1][dx1] != '.') {
        continue;
      }
      int dx2 = x + std::get<0>(neighbor_offsets[(i + 1) % 8]);
      int dy2 = y + std::get<1>(neighbor_offsets[(i + 1) % 8]);
      if (dx2 < 0 || dx2 >= map_size || dy2 < 0 || dy2 >= map_size || citymap[dy2][dx2] != '.') {
        continue;
      }
      node_list.push_back(Node(nx, ny, cost));
    }
  }
}

void children(int x, int y, const std::vector<std::string>& citymap, std::vector<std::tuple<int, int, double>>& node_list) {
  int map_size = citymap.size();
  for (int i=0;i < 8;i++) {
    const auto& [dx, dy, cost] = neighbor_offsets[i];
    int nx = x + dx;
    int ny = y + dy;
    if (nx < 0 || nx >= map_size || ny < 0 || ny >= map_size || citymap[ny][nx] != '.') {
      continue;
    }
    if (i % 2 != 0) {
      int dx1 = x + std::get<0>(neighbor_offsets[i-1]);
      int dy1 = y + std::get<1>(neighbor_offsets[i-1]);
      if (dx1 < 0 || dx1 >= map_size || dy1 < 0 || dy1 >= map_size || citymap[dy1][dx1] != '.') {
        continue;
      }
      int dx2 = x + std::get<0>(neighbor_offsets[(i + 1) % 8]);
      int dy2 = y + std::get<1>(neighbor_offsets[(i + 1) % 8]);
      if (dx2 < 0 || dx2 >= map_size || dy2 < 0 || dy2 >= map_size || citymap[dy2][dx2] != '.') {
        continue;
      }
    }
    node_list.emplace_back(nx, ny, cost);  
  }
}

void children(Node node, const std::vector<std::string>& citymap, std::vector<Node>& node_list) {
  children(node.x, node.y, citymap, node_list);
}

