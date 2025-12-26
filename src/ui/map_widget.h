#pragma once
#include "scenario.h"
//#include "tools.h"
#include "conversions.h"
#include <QWidget>
#include <QPainter>
/*
bit scheme
bit 7: open/closed renamed to WALL since that's what we might draw
bit 6: start 
bit 5: goal
bit 4: f_visited
bit 3: f_expanded
bit 2: a_visited
bit 1: a_expanded
bit 0: reserved
*/
// Bitwise ops
constexpr std::uint8_t WALL         = 1u << 7;
constexpr std::uint8_t START        = 1u << 6;
constexpr std::uint8_t GOAL         = 1u << 5;
constexpr std::uint8_t VISIT_F      = 1u << 4;
constexpr std::uint8_t EXPAND_F     = 1u << 3;
constexpr std::uint8_t VISIT_A      = 1u << 2;
constexpr std::uint8_t EXPAND_A     = 1u << 1;
constexpr std::uint8_t FOUND        = 1u << 0;

constexpr std::uint8_t CLEAR_SCENARIO = WALL;
constexpr std::uint8_t CLEAR_FRINGE = ~(VISIT_F | EXPAND_F);
constexpr std::uint8_t CLEAR_ASTAR = ~(VISIT_A | EXPAND_A);

/* 
* index = size * y + x
*/

class MapWidget : public QWidget {
    Q_OBJECT;
public:
    MapWidget(int size = 0, QWidget* parent = nullptr);
    // explicit MapWidget(int size, QWidget* parent = nullptr);
    void setMap(std::vector<std::string>  citymap);
    void setScenario(Scenario scenario);
    int showHideFringe();
    int showHideAstar();

protected:
    void paintEvent(QPaintEvent* ev) override;

private:
    QImage img;
    std::vector<uint8_t> storage;
    int size;

    // void setMap(std::vector<std::string>  citymap);
    void visit_astar(QVector<QPoint> vec);
    void visit_fringe(QVector<QPoint> vec);
    void expand_astar(QPoint point);
    void expand_fringe(QPoint point);
    void clear();
    void clear_scenario();
    void clear_fringe();
    void clear_astar();
};

