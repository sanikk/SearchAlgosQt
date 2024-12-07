#include "scenario_controls.h"

ScenarioControls::ScenarioControls(ScenarioService& i_scenario_service) : scenario_service(i_scenario_service) {
  QVBoxLayout *controlsLayout = new QVBoxLayout{};
  bucket_box = new QComboBox{};
  controlsLayout->addWidget(bucket_box);
  scenario_box = new QComboBox{};
  controlsLayout->addWidget(scenario_box);
  setLayout(controlsLayout);

  connect(bucket_box, &QComboBox::currentIndexChanged, this, &ScenarioControls::updateScenarioBox);
}

void ScenarioControls::updateBucketBox() {
  bucket_box->clear();
  QStringList bucket_list;
  auto ret_value = scenario_service.get_bucket_list();
  for (int &bucket : scenario_service.get_bucket_list()) {
    bucket_list.append(QString("%1: %2-%3").arg(bucket).arg((bucket)*10).arg((bucket + 1) * 10 - 1));
  }
  bucket_box->addItems(bucket_list);
}

void ScenarioControls::updateScenarioBox(int index) {
  scenario_box->clear();
  if (index == -1) {
    return;
  }
  QStringList scenario_list;
  auto bucket_scenarios = scenario_service.get_bucket_scenarios(index);
  for (Scenario &scen : bucket_scenarios) {
    scenario_list.append(QString("%1: ideal_cost %2, (%3,%4) => (%5,%6)").arg(scen.id).arg(scen.cost).arg(scen.start_x).arg(scen.start_y).arg(scen.goal_x).arg(scen.goal_y));
  }
  scenario_box->addItems(scenario_list);
}

