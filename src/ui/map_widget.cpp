#include "map_widget.h"

MapWidget::MapWidget(int i_size, QWidget* parent): QWidget(parent) {
  size = i_size;
  img = QImage(size, size, QImage::Format_RGB32);
  storage.assign(size * size, 0);
}


  //mapScene->setMap(scenarioService.get_map());
  //std::vector<std::string> get_map();
void MapWidget::setMap(std::vector<std::string>  citymap) {
  
}

void MapWidget::setScenario(Scenario scenario) {

}

void MapWidget::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.drawImage(0, 0, img);
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
