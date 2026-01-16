#pragma once
#include "models.h"

#include <optional>

#include <QWidget>
#include <QPainter>


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
    void setMap(std::vector<std::string>  citymap);
    void setScenario(Scenario i_scenario);
    void showHideFringe();
    void showHideAstar();
    bool showFringe;
    bool showAstar;

    bool searching;
    void start_search();
    void stop_search();


public slots:
    void fringeVisit(int x, int y);
    void fringeExpand(int x, int y);
    void fringeFinished(RetVal ret);
    void astarVisit(int x, int y);
    void astarExpand(int x, int y);
    void astarFinished(RetVal ret);


protected:
    void paintEvent(QPaintEvent* ev) override;

private:
    QImage img;
    std::vector<uint8_t> storage;
    int size;
    std::optional<Scenario> scenario;

    QRgb colorPixel(uint8_t byte);
    void renderMap();

    int mapScale = 5;

    void clear_storage();
    void clear_scenario();
    void clear_fringe();
    void clear_astar();
};

