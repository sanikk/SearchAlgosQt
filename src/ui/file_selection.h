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
    ScenarioService& scenarioService;
    void setMapFile(std::filesystem::path& filepath);
    void setScenarioFile(std::filesystem::path& filepath);
    QLabel *scenarioFileLabel;
    QPushButton *scenarioFileButton;
    QLabel *mapFileLabel;
    QPushButton *mapFileButton;
public:
    FileSelection(ScenarioService& i_scenario_service);
private slots:
    void chooseScenarioFile();
    void chooseMapFile();
signals:
    void scenarioFileChanged();
    void mapFileChanged();


};
