#pragma once
#include "scenario_service.h"
#include <QBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <filesystem>


class ScenarioControls : public QGroupBox {
    // ScenarioService scenario_service;
public:
    ScenarioControls(ScenarioService& i_scenario_service);
private slots:
    void chooseScenarioFile();
    void setScenarioFile(std::filesystem::path filepath);
    void chooseMapFile();
    void setMapFile(std::filesystem::path filepath);
private:
    QLabel *scenario_file_label;
    QPushButton *scenario_file_button;
    QLabel *map_file_label;
    QPushButton *map_file_button;
    ScenarioService& scenario_service;
};
