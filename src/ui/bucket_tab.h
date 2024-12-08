#pragma once
#include "scenario_service.h"
#include "search_service.h"
#include <QWidget>
#include <QBoxLayout>
#include <QTableWidget>
#include <QPushButton>

class BucketTab : public QWidget {
    Q_OBJECT;

public:
    BucketTab(ScenarioService& scenario_service, SearchService& i_search_service);
public slots:
    void updateTableScenarios(int index);
    void run_astar();
    void run_fringe();

private:
    ScenarioService& scenario_service;
    SearchService& search_service;

    QTableWidget *result_table;
    QTableWidget* get_result_table();
    QWidget* get_run_box();
    QWidget *run_box;
    QPushButton *astar_button;
    QPushButton *fringe_button;
};
