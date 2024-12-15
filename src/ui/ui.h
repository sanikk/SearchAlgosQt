#pragma once
#include "scenario_controls.h"
#include "scenario_service.h"
#include "search_service.h"
#include "search_tabs.h"
#include "bucket_tab.h"
#include "file_selection.h"
#include <QTabWidget>
#include <QWidget>


class Ui: public QWidget {
    Q_OBJECT;

public:
    Ui(ScenarioService& scenario_service, SearchService& search_service);

private:
    ScenarioControls *scenario_controls;

    QTabWidget *tab_window;

    FileSelection *file_selection_tab;
    BucketTab *bucket_tab;
    SearchTab *search_tab;
};

