#pragma once
#include <QBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>


class ScenarioControls : public QGroupBox {
    // ScenarioService scenario_service;
public:
    ScenarioControls();
private slots:
    void setScenarioFile();
private:
    QPushButton *scenario_file_button;
};
