#include "map_scene.h"
// #include <iostream>

MapScene::MapScene() : QGraphicsScene(), basemapItem(nullptr), startGoalItem(nullptr), map_size(0), astarLayer(nullptr), fringeLayer(nullptr)
{

}

MapScene::MapScene(const std::vector<std::string>& citymap, const Scenario& scenario)
  : QGraphicsScene(),basemapItem(addPixmap(get_bitmap(citymap))), map_size(citymap.size()),
    astarLayer(new PaintableLayer{int(citymap.size()), 3}), fringeLayer(new PaintableLayer{int(citymap.size()), 4})
{
}

void MapScene::setMap(const std::vector<std::string>& citymap) {
  clear(); 
  map_size = citymap.size();
  QBitmap basemap = get_bitmap(citymap);
  basemapItem = addPixmap(basemap);
  basemapItem->setZValue(1);
}

void MapScene::setScenario(const Scenario& scenario) {
  if (!basemapItem) {
    qDebug() << "setScenario: basemapItem not set!";
    return;
  }
  // std::cout << "scenario changed to " << scenario << std::endl;
  // qDebug() << scenario;
  setStartGoalLayer(scenario);
  if (astarLayer) {
    astarLayer->clear();
  } else {
    astarLayer = new PaintableLayer{map_size, 3};
    addItem(astarLayer);
  }
  if (fringeLayer) {
    fringeLayer->clear();
  } else {
    fringeLayer = new PaintableLayer{map_size, 4};
    addItem(fringeLayer);
  }
  // testing drawing on layers here:
  // QVector<QPoint> vec1;
  // QVector<QPoint> vec2;
  // for (int i=1; i < 10; i++) {
  //   vec1.push_back(QPoint(i, 1));
  //   vec2.push_back(QPoint(1, i));
  //   fringeLayer->expand(QPoint(i, 2));
  //   astarLayer->expand(QPoint(2,i));
  // }
  // fringeLayer->visit(vec1);
  // astarLayer->visit(vec2);
}

QBitmap MapScene::get_bitmap(const std::vector<std::string>& citymap) {
  if (map_size == 0) {
    qDebug() << "map size was 0";
    return QBitmap();
  }
  QImage map_image(map_size, map_size, QImage::Format_Mono);
  for (int row=0; row < citymap.size(); row++) {
    for (int col=0; col < citymap[0].size();col++) {
      if (citymap[row][col] == '.') {
        map_image.setPixel(col, row, 1);
      }
    }
  }
  return QBitmap::fromImage(map_image);
}

void MapScene::setStartGoalLayer(const Scenario& scenario) {
  if (map_size==0) {
    qDebug() << "basemap not set";
    return;
  }
  startGoalPixmap = QPixmap(map_size, map_size);
  // startGoalPixmap.fill(Qt::red);
  drawCross(scenario.start_x, scenario.start_y, start_color);
  drawCross(scenario.goal_x,scenario.goal_y, goal_color);
  if (!startGoalItem) {
    startGoalItem = new QGraphicsPixmapItem{startGoalPixmap};
    startGoalItem->setZValue(2);
    // startGoalItem->setOpacity(0.5);
    addItem(startGoalItem);
  } else {
    startGoalItem->setPixmap(startGoalPixmap);
  }
  // startGoalItem->setVisible(true);
}

void MapScene::drawCross(const int& x, const int& y, const uint& index_or_rgb) {
  if (!basemapItem || !startGoalPixmap || map_size < 2) {
    return;
  }
  QPainter painter(&startGoalPixmap);
  
  painter.setPen(QColor(index_or_rgb));
  painter.drawLine(std::max(0, x-2), y, std::min(map_size - 1, x + 2), y);
  painter.drawLine(x, std::max(0, y-2), x, std::min(map_size - 1, y+2));
}

// SLOTS:

int MapScene::showHideFringe() {
  if (!fringeLayer) {
    return 0;
  }
  if (fringeLayer->isVisible()) {
    fringeLayer->setVisible(false);
    return 2;
  } else {
    fringeLayer->setVisible(true);
    return 1;
  }
}

int MapScene::showHideAstar() {
  if (!astarLayer) {
    return 0;
  }
  if (astarLayer->isVisible()) {
    astarLayer->setVisible(false);
    return 2;
  } else {
    astarLayer->setVisible(true);
    return 1;
  }
}

//

void MapScene::visitAstar(QVector<QPoint> vec) {
  if (!astarLayer) {
    return;
  }
  astarLayer->visit(vec);

}

void MapScene::expandAstar(QPoint point) {
  if (!astarLayer) {
    return;
  }
  astarLayer->expand(point);

}

void MapScene::visitFringe(QVector<QPoint> vec) {
  if (!fringeLayer) {
    return;
  }
  fringeLayer->visit(vec);
}

void MapScene::expandFringe(QPoint point ) {
  if (!fringeLayer) {
    return;
  }
  fringeLayer->expand(point);
}






PaintableLayer::PaintableLayer(int map_size, int layer_z_level) : QGraphicsItem(), layer_map(map_size, std::vector<int>(map_size, 0)) {
  size = map_size;
  setZValue(layer_z_level);
}


QRectF PaintableLayer::boundingRect() const {
  return QRectF(0 , 0, size, size);
}

void PaintableLayer::paint(QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* parent) {
  QColor expanded(0, 255, 0);
  QColor visited(0,0,255);
  for (int y=0;y < size; y++) {
    for (int x=0;x < size;x++) {
      int val = layer_map[y][x];
      if (val == 0) {
        continue;
      } else if (val == 1) {
        painter->setPen(visited);
        painter->drawPoint(x,y);
      } else if (val == 2) {
        painter->setPen(expanded);
        painter->drawPoint(x,y);
      }
    }
  }
}

void PaintableLayer::visit(QVector<QPoint> vec) {
  for (QPoint point : vec) {
    if (layer_map[point.y()][point.x()] == 2) {
      continue;
    }
    layer_map[point.y()][point.x()] = 1;
  }
}

void PaintableLayer::expand(QPoint point) {
  layer_map[point.y()][point.x()] = 2;
}

void PaintableLayer::clear() {
  layer_map = std::vector<std::vector<int>>(size, std::vector<int>(size, 0));
}
