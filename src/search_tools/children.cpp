#include "children.h"
#include "cell_flags.h"
#include "conversions.h"


void SearchTools::children(int x, int y, const std::vector<std::string>& citymap, std::vector<Node>& node_list) {
  int map_size = citymap.size();
  for (int i=0;i < 8;i++) {
    if (x==0 && (i == 1 || i == 2 || i == 3)) continue; 
    if (x==map_size - 1 && (i==5 || i == 6 || i == 7)) continue;
    if (y==0 && (i == 3 || i == 4 || i == 5)) continue;
    if (y==map_size - 1 && (i == 7 || i == 0 || i == 1)) continue;
    const auto& [dx, dy, cost] = neighbor_offsets[i];
    int nx = x + dx;
    int ny = y + dy;
    if (citymap[ny][nx] != '.') {
      continue;
    }
    if (i % 2 == 0) {
      node_list.push_back(Node(nx, ny, cost));
    } else {
      int dx1 = x + std::get<0>(neighbor_offsets[i-1]);
      int dy1 = y + std::get<1>(neighbor_offsets[i-1]);
      int dx2 = x + std::get<0>(neighbor_offsets[(i + 1) % 8]);
      int dy2 = y + std::get<1>(neighbor_offsets[(i + 1) % 8]);
      if (citymap[dy1][dx1] != '.' && citymap[dy2][dx2] != '.') continue;
      node_list.emplace_back(Node(nx, ny, ny * citymap.size() + nx, cost));
    }
  }
}

void SearchTools::children(int x, int y, const std::vector<std::string>& citymap, std::vector<std::tuple<int, int, double>>& node_list) {
  int map_size = citymap.size();
  for (int i=0;i < 8;i++) {
    if (x==0 && (i == 1 || i == 2 || i == 3)) continue; 
    if (x==map_size - 1 && (i==5 || i == 6 || i == 7)) continue;
    if (y==0 && (i == 3 || i == 4 || i == 5)) continue;
    if (y==map_size - 1 && (i == 7 || i == 0 || i == 1)) continue;
    const auto& [dx, dy, cost] = neighbor_offsets[i];
    int nx = x + dx;
    int ny = y + dy;
    if (citymap[ny][nx] != '.') {
      continue;
    }
    if (i % 2 != 0) {
      int dx1 = x + std::get<0>(neighbor_offsets[i-1]);
      int dy1 = y + std::get<1>(neighbor_offsets[i-1]);
      int dx2 = x + std::get<0>(neighbor_offsets[(i + 1) % 8]);
      int dy2 = y + std::get<1>(neighbor_offsets[(i + 1) % 8]);
      if (citymap[dy1][dx1] != '.' && citymap[dy2][dx2] != '.') continue;
    }
    node_list.emplace_back(nx, ny, cost);  
  }
}

void SearchTools::children(Node node, const std::vector<std::string>& citymap, std::vector<Node>& node_list) {
  children(node.x, node.y, citymap, node_list);
}

ChildrenNodes::ChildrenNodes(const int width, 
                             const int heigth, const std::vector<uint8_t>& citymap) : 
  Children(width, heigth, citymap),
  offsets_(std::array<NodeOffset, 8>{{
    {0, -1, -width_, 1.0},
    {-1, -1, -width_ - 1, DIAG},
    {-1, 0, -1, 1.0},
    {-1, 1, width_ - 1, DIAG},
    {0, 1, width_, 1.0},
    {1, 1, width_ + 1, DIAG},
    {1, 0, 1, 1.0},
    {1, -1, -width_+1, DIAG}
  }}) 
{
}

void ChildrenNodes::children(Node current) {
  for (int i=0;i < 8;i++) {

    if (current.x < 1 && (i == 1 || i == 2 || i == 3)) continue; 
    if (current.x > width_ - 2 && (i==5 || i == 6 || i == 7)) continue;
    if (current.y < 1 && (i == 7 || i == 0 || i == 1)) continue;
    if (current.y > height_ - 2 && (i == 3 || i == 4 || i == 5)) continue;
    
    NodeOffset current_offset = offsets_[i];
    int ni = current.index + current_offset.index_delta;

    if ((*citymap_)[ni] & WALL) continue;
    
    if (i % 2 != 0) { // with diagonals we need to check the neighbors to see if there's a way.
      int di1 = current.index + offsets_[i-1].index_delta;
      int di2 = current.index + offsets_[(i+1) % 8].index_delta;
      if ((*citymap_)[di1] & WALL && (*citymap_)[di2] & WALL) continue;
    }
    out_nodes_.emplace_back(current.x + current_offset.x_delta,
                            current.y + current_offset.y_delta,
                            ni, 
                            current_offset.cost);
  }
}

std::vector<Node> ChildrenNodes::get_nodes(Node current) {
  out_nodes_.clear();
  ChildrenNodes::children(current);
  return out_nodes_;
  
}
ChildrenTuples::ChildrenTuples(const int width, const int height, const std::vector<uint8_t>& citymap) : Children(width, height, citymap),
  offsets_(std::array<NodeOffset, 8>{{


    {0, -1, -width, 1.0},
    {-1, -1, -width - 1, DIAG},
    {-1, 0, -1, 1.0},
    {-1, 1, width - 1, DIAG},
    {0, 1, width, 1.0},
    {1, 1, width + 1, DIAG},
    {1, 0, 1, 1.0},
    {1, -1, -width+1, DIAG}

  }}) {}

void ChildrenTuples::children(int current_index) {
  int col = current_index % width_;
  bool on_left = col < 1;
  bool on_right = col > width_ - 2;
  int row = current_index / width_;
  bool on_top = row < 1;
  bool on_bottom = row > height_ - 2;
  auto [current_x, current_y] = int2xy(current_index, width_);
  for (int i=0;i < 8;i++) {
    if (on_left && (i == 1 || i == 2 || i == 3)) continue; 
    if (on_right && (i==5 || i == 6 || i == 7)) continue;
    if (on_top && (i == 3 || i == 4 || i == 5)) continue;
    if (on_bottom && (i == 7 || i == 0 || i == 1)) continue;
    const auto& [delta_x, delta_y, delta_index, cost] = offsets_[i];
    int ni = current_index + delta_index;
     
    if (
      (*citymap_)[ni] & WALL) {
      continue;
    }
    if (i % 2 != 0) { // with diagonals we need to check the neighbors to see if there's a way.
      int di1 = current_index + offsets_[i-1].index_delta;
      int di2 = current_index + offsets_[(i+1) % 8].index_delta;
      if ((
        (*citymap_)[di1] & WALL) && (
        (*citymap_)[di2] & WALL)) continue;
    }
    out_tuples_.emplace_back(current_x + delta_x, current_y + delta_y, ni, cost);  

  }
}

std::vector<std::tuple<int, int, int, double>>& ChildrenTuples::get_tuples(int x, int y) {
  out_tuples_.clear();
  children(y * width_ + x);
  return out_tuples_;

}

std::vector<std::tuple<int, int, int, double>>& ChildrenTuples::get_tuples(int current_index) {
  out_tuples_.clear();
  children(current_index);
  return out_tuples_;
}
