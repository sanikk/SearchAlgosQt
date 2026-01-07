#include "scenario_controls.h"

ScenarioControls::ScenarioControls(ScenarioService& i_scenario_service) : scenarioService(i_scenario_service) {
  QVBoxLayout *controlsLayout = new QVBoxLayout{};
  bucketBox = new QComboBox{};
  controlsLayout->addWidget(bucketBox);
  scenarioBox = new QComboBox{};
  controlsLayout->addWidget(scenarioBox);
  setLayout(controlsLayout);

  connect(bucketBox, &QComboBox::currentIndexChanged, this, &ScenarioControls::updateScenarioBox);
  connect(scenarioBox, &QComboBox::currentIndexChanged, this, &ScenarioControls::scenarioSelected);
}

void ScenarioControls::updateBucketBox() {
  bucketBox->clear();
  QStringList bucket_list;
  auto ret_value = scenarioService.get_bucketList();
  for (int &bucket : scenarioService.get_bucketList()) {
    bucket_list.append(QString("%1: %2-%3").arg(bucket).arg((bucket)*10).arg((bucket + 1) * 10 - 1));
  }
  bucketBox->addItems(bucket_list);
}

void ScenarioControls::updateScenarioBox(int index) {
  scenarioBox->clear();
  if (index == -1) {
    return;
  }
  auto bucket_scenarios = scenarioService.get_bucketScenarios(index);
  for (Scenario &scen : bucket_scenarios) {
    scenarioBox->addItem(QString("%1: ideal_cost %2, (%3,%4) => (%5,%6)")
                         .arg(scen.id)
                         .arg(scen.cost)
                         .arg(scen.start_x)
                         .arg(scen.start_y)
                         .arg(scen.goal_x)
                         .arg(scen.goal_y), scen.id);
  }
}

int ScenarioControls::get_bucketIndex() {
  return bucketBox->currentIndex();
}

int ScenarioControls::get_scenarioIndex() {
  return scenarioBox->currentData().toInt();
}

void ScenarioControls::scenarioSelected(int index) {
  if (index == -1) {
    return;
  }
  scenarioChanged(bucketBox->currentData().toInt());
}
