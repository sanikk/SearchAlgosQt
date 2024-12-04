#pragma once
#include "scenario_service.h"
#include "scenario_controls.h"
#include <QWidget>


class Ui: public QWidget {
    Q_OBJECT

public:
    Ui(ScenarioService scenario_service);

private:
    ScenarioControls *scenario_controls;
};

