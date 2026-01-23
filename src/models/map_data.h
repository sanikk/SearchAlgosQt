#pragma once

#include <cstdint>
#include <vector>

class MapData {

public:
  MapData(int map_size = 0) : map_size(map_size) { map_data.assign(map_size * map_size, 0); };
  MapData(int map_size, std::vector<uint8_t> map_data) : map_size(map_size) { map_data.assign(map_size * map_size, 0); };

  int map_size;
  std::vector<uint8_t> map_data;
};
