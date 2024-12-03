#include "scenario_controls.h"


ScenarioControls::ScenarioControls() {
    QVBoxLayout *controls_layout = new QVBoxLayout;
    scenario_file_button = new QPushButton{"&Choose a scenario file"};
    controls_layout->addWidget(scenario_file_button);
    connect(scenario_file_button, &QPushButton::clicked, this, &ScenarioControls::setScenarioFile);
    QLabel *chosen_map_label = new QLabel{"Pick a scenario file first"};
    controls_layout->addWidget(chosen_map_label);
    setLayout(controls_layout);
}

void ScenarioControls::setScenarioFile() {
   QString ret = QFileDialog::getOpenFileName(this, 
         tr("Choose a Scenario File"), ".", tr("Scenario Files (*.map.scen)"));
  if (!ret.isEmpty()) {
    QString new_text;
    if (int index=ret.lastIndexOf("/")) {
      new_text = ret.sliced(index + 1);
    } else {
      new_text=ret;
    }
    scenario_file_button->setText(new_text);
  }
}
