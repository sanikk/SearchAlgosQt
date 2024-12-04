#pragma once
#include "scenario_service.h"
#include <QBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>


class ScenarioControls : public QGroupBox {
    // ScenarioService scenario_service;
public:
    ScenarioControls(ScenarioService& i_scenario_service);
private slots:
    void setScenarioFile();
    void setMapFile();
private:
    QLabel *scenario_file_label;
    QPushButton *scenario_file_button;
    QLabel *map_file_label;
    QPushButton *map_file_button;
    ScenarioService& scenario_service;
};
