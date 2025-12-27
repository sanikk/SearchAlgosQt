#pragma once
#include "scenario_service.h"
#include "search_service.h"
#include "map_widget.h"
#include "fullscreenDialog.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QPushButton>
#include <QPainter>
#include <QScrollArea>


class VisualSearchTab : public QWidget {
    Q_OBJECT;

public:
    VisualSearchTab(ScenarioService& i_scenario_service, SearchService& i_search_service);
public slots:
    void mapChanged();
    void scenarioChanged(int scenario_index);
private:
    ScenarioService& scenarioService;
    SearchService& searchService;
    
    QPushButton *runAstarButton;
    QPushButton *runFringeButton;
    QPushButton *showHideAstarButton;
    QPushButton *showHideFringeButton;
    QPushButton *fullscreenButton;
    QWidget *controlsBox;

    MapWidget *mapScene;
    QScrollArea* scroll;

    QVBoxLayout *tabLayout;
    void showHideFringe();
    void showHideAstar();
    void launchFullscreenDialog();
    void endFullScreenDialog();
};


