#pragma once

#include <cstdint>
#include <vector>

class MapData {

public:
  MapData(int width = 0, int height = 0) : width(width), height(height) { map_data.assign(width * height, 0); }
  MapData(int width, int height, std::vector<uint8_t> map_data) : width(width), height(height), map_data(map_data) {}

  int width, height;
  std::vector<uint8_t> map_data;
};
