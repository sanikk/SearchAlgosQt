#include "scenario_controls.h"

ScenarioControls::ScenarioControls(ScenarioService& i_scenario_service) : scenario_service(i_scenario_service) {
  QVBoxLayout *controlsLayout = new QVBoxLayout{};
  bucket_box = new QComboBox{};
  controlsLayout->addWidget(bucket_box);
  scenario_box = new QComboBox{};
  controlsLayout->addWidget(scenario_box);
  setLayout(controlsLayout);
}
