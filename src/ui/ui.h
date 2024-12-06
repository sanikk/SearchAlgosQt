#pragma once
#include "scenario_service.h"
#include "search_tabs.h"
#include "bucket_tab.h"
#include "file_selection.h"
#include <QTabWidget>
#include <QWidget>


class TabWindow : public QTabWidget {
    Q_OBJECT;

public:
    TabWindow(ScenarioService& scenario_service);
private:
    FileSelection *file_selection_tab;
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

