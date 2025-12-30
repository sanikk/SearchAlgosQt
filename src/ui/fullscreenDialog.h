#pragma once
#include "scenario_controls.h"

#include <QDialog>
#include <QWidget>
#include <QPushButton>
#include <QBoxLayout>
#include <QScrollArea>

class FullscreenDialog : public QDialog {
public:
    FullscreenDialog(QScrollArea *scroll, ScenarioControls* i_scenario_controls);
    QPushButton *runAstarButton;
    QPushButton *runFringeButton;
    QPushButton *showHideAstarButton;
    QPushButton *showHideFringeButton;
    QPushButton *exitFullscreenButton;
private:
    QScrollArea *scroll;
    ScenarioControls* scenario_controls;
};
