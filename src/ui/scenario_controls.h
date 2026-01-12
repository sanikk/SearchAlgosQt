#pragma once

#include "scenario_service.h"

#include <QComboBox>
#include <QVBoxLayout>

class ScenarioControls : public QWidget {
    Q_OBJECT;
public:
    ScenarioControls(ScenarioService& i_scenario_service);
    QComboBox *bucketBox;
    QComboBox *scenarioBox;
    int get_bucketIndex();
    int get_scenarioIndex();
private:
    ScenarioService& scenarioService;
public slots:
    void updateBucketBox();
    void updateScenarioBox(int index);
    void scenarioSelected(int index);
signals:
    void scenarioChanged(int);
};

