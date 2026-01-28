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
    QPushButton *run_astar_button;
    QPushButton *run_fringe_button;
    QPushButton *show_hide_astar_button;
    QPushButton *show_hide_fringe_button;
    QPushButton *exit_fullscreen_button;
private:
    QScrollArea *scroll;
    ScenarioControls* scenario_controls;
};
