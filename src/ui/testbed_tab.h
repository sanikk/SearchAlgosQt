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
    TestBedTab(ScenarioService& i_scenario_service, SearchService& i_search_service, ScenarioControls* i_scenario_controls);
public slots:
    void update_table_scenarios(int index);
    void run_test();
    void run_base();

private:
    ScenarioService& scenario_service;
    SearchService& search_service;
    ScenarioControls* scenario_controls;

    QTableWidget *result_table;
    QTableWidget* get_result_table();
    QWidget* get_run_box();
    QWidget *run_box;
    QPushButton *test_button;
    QPushButton *base_button;
    void load_retvals_to_result_table(std::vector<RetVal> retvals, int start_column);
};
