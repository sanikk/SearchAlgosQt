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


class Ui: public QWidget {
    Q_OBJECT;

public:
    Ui(ScenarioService& i_scenario_service, SearchService& i_searchService);

private:
    ScenarioControls *scenarioControls;

    QTabWidget *tabWindow;

    FileSelection *fileSelectionTab;
    BucketTab *bucketTab;
    VisualSearchTab *visualSearchTab;
    TestBedTab *testBedTab;
};

