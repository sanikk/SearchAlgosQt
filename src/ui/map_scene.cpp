#include "map_scene.h"
#include <iostream>

MapScene::MapScene() : QGraphicsScene(), basemap(nullptr)
{

}

MapScene::MapScene(const std::vector<std::string>& citymap, const Scenario& scenario)
  : QGraphicsScene(),basemap(get_bitmap(citymap))
{
  addPixmap(basemap);
}

void MapScene::setMap(const std::vector<std::string>& citymap) {
  clear();
  basemap = get_bitmap(citymap);
  addPixmap(basemap);
}

void MapScene::setScenario(const Scenario& scenario) {
  std::cout << "scenario changed to " << scenario << std::endl;
}

QBitmap MapScene::get_bitmap(const std::vector<std::string>& citymap) {
  int map_size = citymap.size();
  QImage map_image(map_size, map_size, QImage::Format_Mono);
  for (int row=0; row < citymap.size(); row++) {
    for (int col=0; col < citymap[0].size();col++) {
      if (citymap[row][col] == '.') {
        map_image.setPixel(row, col, 1);
      }
    }
  }
  return QBitmap::fromImage(map_image);
}

QImage* MapScene::get_layer(int map_size) {
  QImage* layer = new QImage{map_size, map_size, QImage::Format_RGB32};
  return layer;
}
