#pragma once
#include "scenario_controls.h"
#include "scenario_service.h"
#include "search_service.h"
#include <QWidget>
#include <QBoxLayout>
#include <QTableWidget>
#include <QPushButton>

class TestBedTab : public QWidget {
    Q_OBJECT;

public:
    TestBedTab(ScenarioService& i_scenario_service, SearchService& i_search_service, ScenarioControls& i_scenario_controls);
public slots:
    void updateTableScenarios(int index);
    void runTest();
    void runBase();

private:
    ScenarioService& scenarioService;
    SearchService& searchService;
    ScenarioControls& scenarioControls;

    QTableWidget *resultTable;
    QTableWidget* get_resultTable();
    QWidget* get_runBox();
    QWidget *runBox;
    QPushButton *testButton;
    QPushButton *baseButton;
    void load_retvals_to_resultTable(std::vector<RetVal> retvals, int start_column);
};
