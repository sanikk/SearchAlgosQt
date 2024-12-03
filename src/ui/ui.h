#pragma once
#include "scenario_controls.h"
#include <QWidget>


class Ui: public QWidget {
    Q_OBJECT

public:
    Ui();

private:
    ScenarioControls *scenario_controls;
};

