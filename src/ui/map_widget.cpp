#include "map_widget.h"

#include <QWindow>


MapWidget::MapWidget(int i_size, QWidget* parent) 
  : QWidget(parent), 
  img(QImage(i_size, i_size, QImage::Format_RGB32)),
  searching(false) 
{
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


void MapWidget::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.scale(map_scale, map_scale);
    p.drawImage(0, 0, img);
}

void MapWidget::render_map(std::vector<int> map_data, int map_size) {
  img = QImage(map_size, map_size, QImage::Format_RGB32);
  int i = 0;
  for (int y=0;y < img.height();y++) {
    QRgb* row = reinterpret_cast<QRgb*>(img.scanLine(y));
    for (int x=0; x < img.width(); x++) {
      row[x] = DEFAULT_BIT_PALETTE[map_data[i]];
      i++;
    } 
  }
  resize(img.height()*map_scale, img.width()*map_scale);
  windowHandle()->requestUpdate();
}

void MapWidget::draw_pixel(int x, int y, int color_index) {
  img.setPixel(x, y, DEFAULT_BIT_PALETTE[color_index]);
  windowHandle()->requestUpdate();
}

