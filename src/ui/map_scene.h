#pragma once
#include "models.h"
// #include "graphics_image_item.h"
// #include "scenario_service.h"
// #include "search_service.h"
#include <QGraphicsScene>
#include <QBitmap>
#include <QImage>
#include <string>
#include <QPainter>

class MapScene : public QGraphicsScene {
    Q_OBJECT;
public:
    // MapScene(const ScenarioService& i_scenario_service, const SearchService& i_search_service);
    MapScene();
    MapScene(const std::vector<std::string>& citymap, const Scenario& scenario);
    void setMap(const std::vector<std::string>& citymap);
    void setScenario(const Scenario& scenario);
    QImage* get_layer(const int map_size);
    QBitmap get_bitmap(const std::vector<std::string>& citymap); 
private:
    // const ScenarioService& scenario_service;
    // const SearchService& search_service;
    QBitmap basemap;
    // GraphicsImageItem *astar_item_layer;
    // GraphicsImageItem *fringe_item_layer;
    // QImage *astar_layer;
    // QImage *fringe_layer;
};
