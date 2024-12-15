#pragma once
#include "scenario_service.h"
#include "search_service.h"
#include "map_scene.h"
#include "fullscreenDialog.h"

#include <QBoxLayout>
#include <QComboBox>
#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QPushButton>


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
    QWidget *controlsBox;

    MapScene *map_scene;
    QGraphicsView *view;

    QVBoxLayout *tabLayout;
    void showHideFringe();
    void showHideAstar();
    void launchFullscreenDialog();
    void endFullScreenDialog();
};


