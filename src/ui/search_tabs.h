#pragma once
#include "scenario_controls.h"
#include "scenario_service.h"
#include "search_service.h"
#include "map_scene.h"

#include <QBoxLayout>
#include <QComboBox>
#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QPushButton>
#include <qtmetamacros.h>


class SearchTab : public QWidget {
    Q_OBJECT;

public:
    SearchTab(ScenarioService& i_scenario_service, SearchService& i_search_service, ScenarioControls& i_scenario_controls);
public slots:
    void mapChanged();
private:
    ScenarioService& scenario_service;
    SearchService& search_service;
    ScenarioControls& scenario_controls;
    
    QPushButton *run_astar_button;
    QPushButton *run_fringe_button;

    MapScene *map_scene;
    QGraphicsView *view;
};


