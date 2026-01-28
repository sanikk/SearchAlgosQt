#include "scenario_controls.h"

ScenarioControls::ScenarioControls(ScenarioService& i_scenario_service) : scenario_service(i_scenario_service) {
  QVBoxLayout *controls_layout = new QVBoxLayout{};
  bucket_box = new QComboBox{};
  controls_layout->addWidget(bucket_box);
  scenario_box = new QComboBox{};
  controls_layout->addWidget(scenario_box);
  setLayout(controls_layout);

  connect(bucket_box, &QComboBox::currentIndexChanged, this, &ScenarioControls::update_scenario_box);
  connect(scenario_box, &QComboBox::currentIndexChanged, this, &ScenarioControls::scenario_selected);
}

void ScenarioControls::update_bucket_box() {
  bucket_box->clear();
  QStringList bucket_list;
  for (int &bucket : scenario_service.get_bucket_list()) {
    bucket_list.append(QString("%1: %2-%3").arg(bucket).arg((bucket)*10).arg((bucket + 1) * 10 - 1));
  }
  bucket_box->addItems(bucket_list);
}

void ScenarioControls::update_scenario_box(int index) {
  scenario_box->clear();
  if (index == -1) {
    return;
  }
  auto bucket_scenarios = scenario_service.get_bucket_scenarios(index);
  for (Scenario &scen : bucket_scenarios) {
    scenario_box->addItem(QString("%1: ideal_cost %2, (%3,%4) => (%5,%6)")
                         .arg(scen.id)
                         .arg(scen.cost)
                         .arg(scen.start_x)
                         .arg(scen.start_y)
                         .arg(scen.goal_x)
                         .arg(scen.goal_y), scen.id);
  }
}

int ScenarioControls::get_bucket_index() {
  return bucket_box->currentIndex();
}

int ScenarioControls::get_scenario_index() {
  return scenario_box->currentData().toInt();
}

void ScenarioControls::scenario_selected(int index) {
  if (index == -1) {
    return;
  }
  emit scenario_changed(get_scenario_index());
}
