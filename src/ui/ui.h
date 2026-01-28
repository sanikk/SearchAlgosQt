#pragma once

#include "scenario_controls.h"
#include "scenario_service.h"
#include "search_service.h"
#include "visual_search_tab.h"
#include "bucket_tab.h"
#include "file_selection.h"
#include "testbed_tab.h"

#include <QTabWidget>
#include <QWidget>
#include <QBoxLayout>


class Ui: public QWidget {
    Q_OBJECT;

public:
    Ui(ScenarioService& i_scenario_service, SearchService& i_search_service);

private:
    void close_fullscreen_dialog();
    ScenarioControls *scenario_controls;

    QVBoxLayout *main_layout;
    QTabWidget *tab_window;


    FileSelection *file_selection_tab;
    BucketTab *bucket_tab;
    VisualSearchTab *visual_search_tab;
    TestBedTab *test_bed_tab;
};

