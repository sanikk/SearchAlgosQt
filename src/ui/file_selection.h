#pragma once
#include "scenario_service.h"
#include <filesystem>
#include <QBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>


class FileSelection : public QWidget {
    Q_OBJECT;
private:
    ScenarioService& scenario_service;
    void setMapFile(std::filesystem::path filepath);
    void setScenarioFile(std::filesystem::path filepath);
    QLabel *scenario_file_label;
    QPushButton *scenario_file_button;
    QLabel *map_file_label;
    QPushButton *map_file_button;
public:
    FileSelection(ScenarioService& i_scenario_service);
private slots:
    void chooseScenarioFile();
    void chooseMapFile();
};
