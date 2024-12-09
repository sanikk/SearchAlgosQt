#pragma once
#include "scenario_controls.h"
#include "scenario_service.h"
#include "search_service.h"
#include <QWidget>
#include <QBoxLayout>
#include <QTableWidget>
#include <QPushButton>

class BucketTab : public QWidget {
    Q_OBJECT;

public:
    BucketTab(ScenarioService& scenario_service, SearchService& i_search_service, ScenarioControls& scenario_controls);
public slots:
    void updateTableScenarios(int index);
    void run_astar();
    void run_fringe();

private:
    ScenarioService& scenario_service;
    SearchService& search_service;
    ScenarioControls& scenario_controls;

    QTableWidget *result_table;
    QTableWidget* get_result_table();
    QWidget* get_run_box();
    QWidget *run_box;
    QPushButton *astar_button;
    QPushButton *fringe_button;
    void load_retvals_to_table(std::vector<RetVal> retvals, int start_column);
};
