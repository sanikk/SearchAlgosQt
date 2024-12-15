#include <QGraphicsItem>
#include <QImage>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

class GraphicsImageItem : public QGraphicsItem, QImage {

public:
    GraphicsImageItem(int height, int widht, QImage::Format format, QGraphicsItem *parent = nullptr);
    GraphicsImageItem(int height, int widht, QImage::Format format, int zlevel, QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;
   
    void paint(QPainter*, const QStyleOptionGraphicsItem* item, QWidget* = nullptr) override;
private:

    void drawSquare(int x, int y, uint index_or_rgb);
};


