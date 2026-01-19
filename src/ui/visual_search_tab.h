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
#include <QLabel>


class VisualSearchTab : public QWidget {
    Q_OBJECT;

public:
    VisualSearchTab(ScenarioService& i_scenario_service, SearchService& i_search_service, ScenarioControls* scenario_controls);
public slots:
    void mapChanged();
    void scenarioChanged(int scenario_index);

    void visit_astar();
    void expand_astar();
    void cost_astar();
    void reset_astar();

    void visit_fringe();
    void expand_fringe();
    void cost_fringe();
    void reset_fringe();
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

    void make_connections();
    QWidget* make_controls_box();
    QHBoxLayout* make_buttons_row();
    QWidget* make_status_rows();
    QLabel* make_label(QString text);

    QLabel* astar_visited;
    QLabel* astar_expanded;
    QLabel* astar_cost;

    QLabel* fringe_visited;
    QLabel* fringe_expanded;
    QLabel* fringe_cost;
    QLabel* fringe_flimit;

    // TODO: these will go in SearchService
    int astar_visits, astar_expands;
    int fringe_visits, fringe_expands;
    double fringe_costs, astar_costs, fringe_flimits;

private slots:
    void showHideFringe();
    void runFringe();
    void runAstar();
    void showHideAstar();
    void launchFullscreenDialog();
    void endFullScreenDialog();

};


