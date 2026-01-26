#include "children.h"

void SearchTools::children(int x, int y, const std::vector<std::string>& citymap, std::vector<Node>& node_list) {
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
      int dx2 = x + std::get<0>(neighbor_offsets[(i + 1) % 8]);
      int dy2 = y + std::get<1>(neighbor_offsets[(i + 1) % 8]);
      if ((dx1 < 0 || dx1 >= map_size || dy1 < 0 || dy1 >= map_size || citymap[dy1][dx1] != '.') &&
(dx2 < 0 || dx2 >= map_size || dy2 < 0 || dy2 >= map_size || citymap[dy2][dx2] != '.')) continue;
      node_list.emplace_back(Node(nx, ny, cost));
    }
  }
}

void SearchTools::children(int x, int y, const std::vector<std::string>& citymap, std::vector<std::tuple<int, int, double>>& node_list) {
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
      int dx2 = x + std::get<0>(neighbor_offsets[(i + 1) % 8]);
      int dy2 = y + std::get<1>(neighbor_offsets[(i + 1) % 8]);
      if ((dx1 < 0 || dx1 >= map_size || dy1 < 0 || dy1 >= map_size || citymap[dy1][dx1] != '.') && (dx2 < 0 || dx2 >= map_size || dy2 < 0 || dy2 >= map_size || citymap[dy2][dx2] != '.')) continue;
    }
    node_list.emplace_back(nx, ny, cost);  
  }
}

void SearchTools::children(Node node, const std::vector<std::string>& citymap, std::vector<Node>& node_list) {
  children(node.x, node.y, citymap, node_list);
}

// void SearchTools::children(Node node, const std::vector<uint8_t>& citymap, std::vector<Node>& node_list) {
//   children(node.x, node.y, citymap, node_list);
// }

Children::Children(const int map_size, const std::vector<uint8_t>& citymap) : map_size_(map_size), citymap_(&citymap), offsets_(std::array<Offset, 8>{{
    {-map_size, 1.0},
    {-map_size - 1, DIAG},
    {-1, 1.0},
    {map_size-1, DIAG},
    {map_size, 1.0},
    {map_size+1, DIAG},
    {1, 1.0},
    {-map_size+1, DIAG}
  }})
{
}
void Children::children(int x, int y) {
  children(y * map_size_ + x);
}
void Children::children(int current_index) {
  for (int i=0;i < 8;i++) {
    const auto& [delta, cost] = offsets_[i];
    int ni = current_index + delta;
    if (ni < 0 || ni >= citymap_->size() || (*citymap_)[ni] & WALL) {
      continue;
    }
    if (i % 2 != 0) { // with diagonals we need to check the neighbors to see if there's a way.
      int di1 = current_index + offsets_[i-1].delta;
      int di2 = current_index + offsets_[(i+1) % 8].delta;
      if ((di1 < 0 || di1 >= citymap_->size() || (*citymap_)[di1] & WALL) && (di2 < 0 || di2 >= citymap_->size() || (*citymap_)[di2] & WALL)) continue;
    }
    out_tuples_.emplace_back(ni, cost);  
  }
}
