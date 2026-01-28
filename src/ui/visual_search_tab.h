#pragma once

#include "fullscreenDialog.h"
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
    void map_changed();
    void scenario_changed(int scenario_index);

    void visit_astar(int x, int y, int value);
    void expand_astar(int x, int y, int value);
    void found_astar(RetVal ret);
    void reset_astar();

    void visit_fringe(int x, int y, int value);
    void expand_fringe(int value);
    void found_fringe(RetVal ret);
    void reset_fringe();

    void redraw_map();
signals:
    void fullscreen_dialog_closed();
private:
    ScenarioService& scenario_service;
    SearchService& search_service;
    ScenarioControls* scenario_controls;
    
    QPushButton *run_astar_button;
    QPushButton *run_fringe_button;
    QPushButton *show_hide_astar_button;
    QPushButton *show_hide_fringe_button;
    QPushButton *fullscreen_button;
    QWidget *controls_box;

    MapWidget *map_scene;
    QScrollArea* scroll;
    QVBoxLayout *tab_layout;

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

    bool show_fringe, show_astar;
    //, fullscreen_dialog;
    FullscreenDialog* fsd = nullptr;

private slots:
    void showHideFringe();
    void runFringe();
    void runAstar();
    void showHideAstar();
    void launchFullscreenDialog();
    void endFullScreenDialog();

};


