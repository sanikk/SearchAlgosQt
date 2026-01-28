#pragma once

#include "scenario_service.h"

#include <QComboBox>
#include <QVBoxLayout>

class ScenarioControls : public QWidget {
    Q_OBJECT;
public:
    ScenarioControls(ScenarioService& i_scenario_service);
    QComboBox *bucket_box;
    QComboBox *scenario_box;
    int get_bucket_index();
    int get_scenario_index();
private:
    ScenarioService& scenario_service;
public slots:
    void update_bucket_box();
    void update_scenario_box(int index);
    void scenario_selected(int index);
signals:
    void scenario_changed(int);
};

