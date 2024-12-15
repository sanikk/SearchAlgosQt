#pragma once
#include "scenario_service.h"
#include <QComboBox>
#include <QVBoxLayout>

class ScenarioControls : public QWidget {
    Q_OBJECT;
public:
    ScenarioControls(ScenarioService& i_scenario_service);
    // TODO: move these to private:
    QComboBox *bucketBox;
    QComboBox *scenarioBox;
    // TODO: remove these functions, handle with signals:
    int get_bucketIndex();
    int get_scenarioIndex();
private:
    ScenarioService& scenarioService;
    // QComboBox *bucket_box;
    // QComboBox *scenario_box;
public slots:
    void updateBucketBox();
    void updateScenarioBox(int index);
    void scenarioSelected(int index);
signals:
    void scenarioChanged(int);
};

