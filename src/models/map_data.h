#include <cstdint>
#include <vector>

class MapData {

public:
  MapData();
  MapData(int map_size, std::vector<uint8_t> map_data);

private:
  int map_size;
  std::vector<uint8_t> map_data;
};
