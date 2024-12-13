#pragma once
#include "models.h"
#include <QGraphicsScene>
#include <QBitmap>
#include <QImage>
#include <QPixmap>
#include <QGraphicsItem>
#include <qtmetamacros.h>
#include <string>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QPoint>
#include <QVector>
#include <QWidget>

class PaintableLayer : public QGraphicsItem {

public:
    PaintableLayer(int map_size, int layer_z_level);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* parent = nullptr) override;
    QRectF boundingRect() const override;
    void clear();
    void visit(QVector<QPoint> vec);
    void expand(QPoint point);
private:
    std::vector<std::vector<int>> layer_map;
    int size;
};

class MapScene : public QGraphicsScene {
    Q_OBJECT;
public:
    MapScene();
    MapScene(const std::vector<std::string>& citymap, const Scenario& scenario);
    void setMap(const std::vector<std::string>& citymap);
    void setScenario(const Scenario& scenario);
    std::tuple<QPixmap, QGraphicsPixmapItem*> get_layer(int map_size, int layer_z_level);
    QBitmap get_bitmap(const std::vector<std::string>& citymap);
    int map_size;

    QGraphicsPixmapItem *start_goal_item;
    PaintableLayer *astar_layer;
    PaintableLayer *fringe_layer;
public slots:
    void visitAstar(QVector<QPoint>);
    void expandAstar(QPoint);
    void visitFringe(QVector<QPoint>);
    void expandFringe(QPoint);
private:
    QGraphicsPixmapItem *basemapItem;
    void setStartGoalLayer(Scenario scenario);
    void drawCross(QPixmap pixmap, int x, int y, uint index_or_rgb);
    void setFringeLayer();
    void setAstarLayer();
};
