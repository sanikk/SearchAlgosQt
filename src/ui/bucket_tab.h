#pragma once
#include "scenario_controls.h"
#include "scenario_service.h"
#include <QWidget>
#include <QBoxLayout>
#include <QTableWidget>

class BucketTab : public QWidget {
    Q_OBJECT;

public:
    BucketTab(ScenarioService& scenario_service);
private slots:


private:
    ScenarioService& scenario_service;
    ScenarioControls *scenario_controls;
    QTableWidget *result_table;
    QTableWidget* get_result_table();

};
