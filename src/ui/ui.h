#pragma once
#include "scenario_service.h"
#include "search_tabs.h"
#include "bucket_tab.h"
#include "scenario_controls.h"
#include <QTabWidget>
#include <qtmetamacros.h>
#include <QWidget>


class TabWindow : public QTabWidget {
    Q_OBJECT;

public:
    TabWindow(ScenarioService& scenario_service);
private:
    ScenarioControls *scenario_controls_tab;
    BucketTab *bucket_tab;
    AstarTab *astar_tab;
    FringeTab *fringe_tab;
};


class Ui: public QWidget {
    Q_OBJECT

public:
    Ui(ScenarioService scenario_service);

private:
    TabWindow *tab_window;
    // ScenarioControls *scenario_controls;
};

