#include "map_widget.h"
#include "conversions.h"

#include <QWindow>


MapWidget::MapWidget(int i_size, QWidget* parent) 
  : QWidget(parent), size(i_size), 
  img(QImage(i_size, i_size, QImage::Format_RGB32)),
  searching(false) 
{
  clear_storage();
  winId();
}


void MapWidget::start_search() {
  //qDebug() << "starting search";
  searching = true;
}

void MapWidget::stop_search() {
  //qDebug() << "stopping search";
  searching = false;
}

void MapWidget::setMap(std::vector<std::string>  citymap) {
  size = citymap.size();
  clear_storage();
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


void MapWidget::setScenario(Scenario i_scenario) {
  scenario = i_scenario;
  clear_scenario();
  if (!scenario.has_value()) {
    return;
  }
  for (int i=-2; i<3; i++) {
    storage[xy2int(std::max(0, std::min(scenario->start_x + i, size - 1)), scenario->start_y, size)] |= START;
    storage[xy2int(scenario->start_x, std::max(0, std::min(scenario->start_y + i, size - 1)), size)] |= START;

    storage[xy2int(std::max(0, std::min(scenario->goal_x + i, size - 1)), scenario->goal_y, size)] |= GOAL;
    storage[xy2int(scenario->goal_x, std::max(0, std::min(scenario->goal_y + i, size - 1)), size)] |= GOAL;
  }
  renderMap();
  windowHandle()->requestUpdate();
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
}

QRgb MapWidget::colorPixel(uint8_t byte) {
  if (showAstar) {
    if (byte & EXPAND_A) {
      return DEFAULT_BIT_PALETTE[7];
    }
    if (byte & VISIT_A) {
      return DEFAULT_BIT_PALETTE[6];
    }

  }
  if (showFringe) {
    if (byte & EXPAND_F) {
      return DEFAULT_BIT_PALETTE[5];
    }
    if (byte & VISIT_F) {
      return DEFAULT_BIT_PALETTE[4];
    }

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
    return DEFAULT_BIT_PALETTE[1];
  }
  return DEFAULT_BIT_PALETTE[0];
}

void MapWidget::showHideAstar() {
  showAstar = !showAstar;
  renderMap();
  windowHandle()->requestUpdate();
}

void MapWidget::showHideFringe() {
  showFringe = !showFringe;
  renderMap();
  windowHandle()->requestUpdate();
}

void MapWidget::astarVisit(int x, int y) {
  uint8_t& cell = storage[xy2int(x,y,size)];
  cell |= VISIT_A;
  if (showAstar && !(cell & EXPAND_A)) {
      img.setPixel(x, y, DEFAULT_BIT_PALETTE[6]);
  }
  windowHandle()->requestUpdate();
}

void MapWidget::astarExpand(int x, int y) {
  storage[xy2int(x, y, size)] |= EXPAND_A;
  if (showAstar) {
    img.setPixel(x, y, DEFAULT_BIT_PALETTE[7]);
  }
  windowHandle()->requestUpdate();
}


void MapWidget::astarFinished(RetVal retval) {
  // TODO: write this
  stop_search();
  //qDebug() << "MapWidget::astarFinished";
  if (retval.cost.has_value()) {
    //qDebug() << "cost was " << retval.cost.value();
  }
  windowHandle()->requestUpdate();
}

void MapWidget::fringeVisit(int x, int y) {
  uint8_t& cell = storage[xy2int(x,y,size)];
  cell |= VISIT_F;
  if (showFringe && !(cell & EXPAND_F)) {
      img.setPixel(x, y, DEFAULT_BIT_PALETTE[4]);
  }
  windowHandle()->requestUpdate();
}

void MapWidget::fringeExpand(int x, int y) {
  storage[xy2int(x, y, size)] |= EXPAND_F;
  if (showFringe) {
    img.setPixel(x, y, DEFAULT_BIT_PALETTE[5]);
  }
  windowHandle()->requestUpdate();
}

void MapWidget::fringeFinished(RetVal retval) {
// TODO: write this
  stop_search();
  windowHandle()->requestUpdate();
}


void MapWidget::clear_storage() {
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

