#pragma once

#include "scenario_service.h"
#include "search_service.h"
#include "map_widget.h"
#include "scenario_controls.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QScrollArea>


class VisualSearchTab : public QWidget {
    Q_OBJECT;

public:
    VisualSearchTab(ScenarioService& i_scenario_service, SearchService& i_search_service, ScenarioControls* scenario_controls);
public slots:
    void mapChanged();
    void scenarioChanged(int scenario_index);
signals:
    void fullscreenDialogClosed();
private:
    ScenarioService& scenario_service;
    SearchService& search_service;
    ScenarioControls* scenario_controls;
    
    QPushButton *runAstarButton;
    QPushButton *runFringeButton;
    QPushButton *showHideAstarButton;
    QPushButton *showHideFringeButton;
    QPushButton *fullscreenButton;
    QWidget *controlsBox;

    MapWidget *mapScene;
    QScrollArea* scroll;
    QVBoxLayout *tabLayout;

private slots:
    void showHideFringe();
    void runFringe();
    void runAstar();
    void showHideAstar();
    void launchFullscreenDialog();
    void endFullScreenDialog();

};


