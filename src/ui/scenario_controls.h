#pragma once
#include "scenario_service.h"
#include <QComboBox>
#include <QVBoxLayout>

class ScenarioControls : public QWidget {
    Q_OBJECT;
public:
    ScenarioControls(ScenarioService& i_scenario_service);
private:
    ScenarioService& scenario_service;
    QComboBox *bucket_box;
    QComboBox *scenario_box;
};

