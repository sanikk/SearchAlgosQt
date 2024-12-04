#include "scenario_controls.h"
#include <filesystem>
#include <qpushbutton.h>

ScenarioControls::ScenarioControls(ScenarioService i_scenario_service) : scenario_service(i_scenario_service) {
    QVBoxLayout *controls_layout = new QVBoxLayout;

    chosen_scenario_file_label = new QLabel{tr("No Scenario File Chosen")};
    controls_layout->addWidget(chosen_scenario_file_label);
    scenario_file_button = new QPushButton{"Choose a &Scenario file"};
    controls_layout->addWidget(scenario_file_button);
    connect(scenario_file_button, &QPushButton::clicked, this, &ScenarioControls::setScenarioFile);

    chosen_map_file_label = new QLabel{"No Map File Chosen"};
    controls_layout->addWidget(chosen_map_file_label);
    map_file_button = new QPushButton{"Choose a &Map file"};
    controls_layout->addWidget(map_file_button);
    connect(map_file_button, &QPushButton::clicked, this, &ScenarioControls::setMapFile);


    setLayout(controls_layout);
}

void ScenarioControls::setScenarioFile() {
  // QString project_root = QDir(QDir(QDir::currentPath()).filePath("..")).absolutePath();
  QString ret = QFileDialog::getOpenFileName(this,
          tr("Choose a Scenario File"), 
          QString::fromStdString(std::filesystem::current_path().parent_path().string()), // cha-cha-chain of FOO-OOLS
          tr("Scenario Files (*.map.scen)"));

  if (!ret.isEmpty()) {
    std::filesystem::path scenario_file(ret.toStdString());
    // scenario
    chosen_scenario_file_label->setText(scenario_file.filename().c_str());
  }
}

void ScenarioControls::setMapFile() {

}
