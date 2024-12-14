#pragma once
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
    SearchTab(ScenarioService& i_scenario_service, SearchService& i_search_service);
public slots:
    void mapChanged();
    void scenarioChanged(int scenario_index);
private:
    ScenarioService& scenario_service;
    SearchService& search_service;
    
    QPushButton *runAstarButton;
    QPushButton *runFringeButton;
    QPushButton *showHideAstarButton;
    QPushButton *showHideFringeButton;
    QPushButton *fullscreenButton;

    MapScene *map_scene;
    QGraphicsView *view;

    void showHideFringe();
    void showHideAstar();
};


