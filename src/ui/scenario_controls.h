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
    // QComboBox *bucket_box;
    // QComboBox *scenario_box;
public slots:
    void updateBucketBox();
    void updateScenarioBox(int index);
};

