#include "map_widget.h"

MapWidget::MapWidget(int i_size, QWidget* parent): QWidget(parent) {
  size = i_size;
  img = QImage(size, size, QImage::Format_RGB32);
  storage.assign(size * size, 0);
}


void MapWidget::setMap(std::vector<std::string>  citymap) {
  size = citymap.size();
  storage.assign(size * size, 0);
  img = QImage(size, size, QImage::Format_RGB32);
  for (int y=0; y < size; y++) {
    for (int x=0; x < size; x++) {
      if (citymap[y][x]=='@') {
        storage[xy2int(x, y, size)] |= WALL;
      }
    } 
  }
  renderMap();
}


void MapWidget::setScenario(Scenario scenario) {
}

void MapWidget::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.scale(mapScale, mapScale);
    p.drawImage(0, 0, img);
}

void MapWidget::renderMap() {
  int i = 0;
  for (int y=0;y < img.height();y++) {
    QRgb* row = reinterpret_cast<QRgb*>(img.scanLine(y));
    for (int x=0; x < img.width(); x++) {
      row[x] = colorPixel(storage[i]);
      i++;
    } 
  }
  resize(img.height()*mapScale, img.width()*mapScale);
  update();
}

QRgb MapWidget::colorPixel(uint8_t byte) {
  if (showAstar) {

  }
  if (showFringe) {

  }
  if (scenario.has_value()) {
    if (byte & START) {
      return DEFAULT_BIT_PALETTE[2];
    }
    if (byte & GOAL) {
      return DEFAULT_BIT_PALETTE[3];
    }
  }
  if (byte & WALL) {
    // std::cout << "wall" << std::endl;
    return DEFAULT_BIT_PALETTE[1];
  }
  return DEFAULT_BIT_PALETTE[0];
}

int MapWidget::showHideAstar() {
  return 0;
}

int MapWidget::showHideFringe() {
  return 0;
}

void MapWidget::visit_fringe(QVector<QPoint> vec) {
  for (QPoint point : vec) {
    storage[xy2int(point.x(), point.y(), size)] |= VISIT_F;
  }
}

void MapWidget::visit_astar(QVector<QPoint> vec) {
  for (QPoint point : vec) {
    storage[xy2int(point.x(), point.y(), size)] |= VISIT_A;
  }
}

void MapWidget::expand_fringe(QPoint point) {
}

void MapWidget::expand_astar(QPoint point) {
}

void MapWidget::clear() {
  storage.assign(size * size, 0); 
}

void MapWidget::clear_scenario() {
  for (int y=0; y < size; y++) {
    for (int x=0; x < size; x++) {
      storage[xy2int(x, y, size)] &= CLEAR_SCENARIO;   
    }
  }
}

void MapWidget::clear_fringe() {
  for (int y=0; y < size; y++) {
    for (int x=0; x < size; x++) {
      storage[xy2int(x, y, size)] &= CLEAR_FRINGE;  
    }
  }
}
void MapWidget::clear_astar() {
  for(int y=0; y < size; y++) {
    for(int x=0; x < size;x++) {
      storage[xy2int(x, y, size)] &= CLEAR_ASTAR;
    }
  }
}

void MapWidget::drawCross(const int& x, const int& y, const uint& index_or_rgb) {
  if (size < 2) {
    return;
  }
  QPainter painter(this);
  
  painter.setPen(QColor(index_or_rgb));
  painter.drawLine(std::max(0, x-2), y, std::min(size - 1, x + 2), y);
  painter.drawLine(x, std::max(0, y-2), x, std::min(size - 1, y+2));
}
