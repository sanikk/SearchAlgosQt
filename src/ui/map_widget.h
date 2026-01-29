#pragma once

#include <QWidget>
#include <QPainter>



/* 
* index = size * y + x
*/

constexpr std::array<QRgb, 9> DEFAULT_BIT_PALETTE = {
    qRgb(255, 255, 255),   // 0 OPEN GROUND white
    qRgb(0,   0,   0),     // 1 WALL black
    qRgb(255, 105, 180),   // 2 START pink
    qRgb(0,   255, 255),   // 3 GOAL cyan
    qRgb(255, 255, 0),     // 4 VISIT_F yellow
    qRgb(0,   255, 0),     // 5 EXPAND_F green
    qRgb(255, 165, 0),     // 6 VISIT_A orange
    qRgb(0,   120, 255),   // 7 EXPAND_A blue
    qRgb(200, 200, 200)    // 8 FOUND light gray
};

class MapWidget : public QWidget {
    Q_OBJECT
public:
    MapWidget(int size = 0, QWidget* parent = nullptr);

    bool searching;
    void start_search();
    void stop_search();


public slots:
    void draw_pixel(int x, int y, int color_index);
    void render_map(std::vector<int> map_data, int map_size);

protected:
    void paintEvent(QPaintEvent* ev) override;

private:
    QImage img;
    int map_scale = 5;

};

