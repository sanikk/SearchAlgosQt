#pragma once
#include "scenario_service.h"
#include <QWidget>
#include <QBoxLayout>
#include <QTableWidget>

class BucketTab : public QWidget {
    Q_OBJECT;

public:
    BucketTab(ScenarioService& scenario_service);
public slots:
    void updateTableScenarios(int index);

private:
    ScenarioService& scenario_service;
    QTableWidget *result_table;
    QTableWidget* get_result_table();

};
