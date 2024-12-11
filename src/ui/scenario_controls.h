#pragma once
#include "scenario_service.h"
#include <QComboBox>
#include <QVBoxLayout>

class ScenarioControls : public QWidget {
    Q_OBJECT;
public:
    ScenarioControls(ScenarioService& i_scenario_service);
    // TODO: move these to private:
    QComboBox *bucket_box;
    QComboBox *scenario_box;
    // TODO: remove these functions, handle with signals:
    int get_bucket_index();
    int get_scenario_index();
private:
    ScenarioService& scenario_service;
    // QComboBox *bucket_box;
    // QComboBox *scenario_box;
public slots:
    void updateBucketBox();
    void updateScenarioBox(int index);
    void scenarioSelected(int index);
signals:
    void scenarioChanged(int);
};

