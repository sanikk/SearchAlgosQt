#pragma once

#include "scenario_service.h"

#include <filesystem>

#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>

class FileSelection : public QWidget {
    Q_OBJECT;
private:
    ScenarioService& scenario_service;
    void set_map_file(std::filesystem::path& filepath);
    void set_scenario_file(std::filesystem::path& filepath);
    QLabel *scenario_file_label;
    QPushButton *scenario_file_button;
    QLabel *map_file_label;
    QPushButton *map_file_button;
public:
    FileSelection(ScenarioService& i_scenario_service);
private slots:
    void choose_scenario_file();
    void choose_map_file();
signals:
    void scenario_file_changed();
    void map_file_changed();


};
