#include "graphics_image_item.h"
#include <iostream>


GraphicsImageItem::GraphicsImageItem(int i_height, int i_width, QImage::Format i_format, QGraphicsItem *parent) 
  : QImage(i_height, i_width, i_format)
{
  drawSquare(1, 1, qRgb(56, 194, 180));
  drawSquare(10,10, qRgb(245, 34, 213));
}
GraphicsImageItem::GraphicsImageItem(int i_height, int i_width, QImage::Format i_format, int i_zlevel, QGraphicsItem *parent)
  : QImage(i_height, i_width, i_format)
{
setZValue(i_zlevel);

drawSquare(1, 1, qRgb(56, 194, 180));
drawSquare(10,10, qRgb(245, 34, 213));
}

QRectF GraphicsImageItem::boundingRect() const {
  std::cout << "boundingRect x: " << x() << ", and y: " << y() << std::endl;
  std::cout << "width: " << width() << ", height: " << height() << std::endl;
  return QRectF(x(),y(),width(),height());
}

void GraphicsImageItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* parent) {
  std::cout << "this x: " << this->x() << ", this y: " << this->y() << std::endl;
  if (!isNull()) {
        painter->setCompositionMode(QPainter::CompositionMode_Source); // Clear previous drawing
        // painter->fillRect(boundingRect(), Qt::transparent); // Or a solid color, like Qt::white
        // painter->draw
        painter->drawImage(QPointF(0,0), *this);
  }
}

void GraphicsImageItem::drawCross(int x, int y, uint index_or_rgb) {
  for (int i=std::max(0, x-2);i < std::min(width(), x + 3) ; i++) {
    setPixel(i, y, index_or_rgb);
  }
  for (int i=std::max(0, y-2);i < std::min(height(), y+3);i++) {
    setPixel(x, i, index_or_rgb);
  }
  update();
}
