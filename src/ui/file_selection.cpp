#include "file_selection.h"

FileSelection::FileSelection(ScenarioService& i_scenario_service) : scenario_service(i_scenario_service) {
    QVBoxLayout *controls_layout = new QVBoxLayout;

    scenario_file_label = new QLabel{tr("No Scenario File Chosen")};
    controls_layout->addWidget(scenario_file_label);
    scenario_file_button = new QPushButton{"Choose a &Scenario file"};
    controls_layout->addWidget(scenario_file_button);
    connect(scenario_file_button, &QPushButton::clicked, this, &FileSelection::chooseScenarioFile);

    map_file_label = new QLabel{"No Map File Chosen"};
    controls_layout->addWidget(map_file_label);
    map_file_button = new QPushButton{"Choose a &Map file"};
    controls_layout->addWidget(map_file_button);
    connect(map_file_button, &QPushButton::clicked, this, &FileSelection::chooseMapFile);

    setLayout(controls_layout);
}

void FileSelection::chooseScenarioFile() {
  QString ret = QFileDialog::getOpenFileName(this,
          tr("Choose a Scenario File"), 
          QString::fromStdString(std::filesystem::current_path().parent_path().string()), // cha-cha-chain of FOO-OOLS
          tr("Scenario Files (*.map.scen)"));
  if (!ret.isEmpty()) {
    std::filesystem::path scenario_file(ret.toStdString());
    setScenarioFile(scenario_file);
  }
}

void FileSelection::setScenarioFile(std::filesystem::path filepath) {
  try {
    // TODO: ok this logic is in the wrong place. ask scenario_service for strings to display.
    if (scenario_service.setScenarioFile(filepath)) {
      scenario_file_label->setText(filepath.filename().c_str());
      std::filesystem::path candidate = filepath.replace_extension();
      if (!candidate.empty() && std::filesystem::is_regular_file(candidate)) {
        setMapFile(candidate);
      }
      emit scenarioFileChanged();
    }
  } catch (const std::invalid_argument& e) {
    qDebug() << e.what();
    // TODO:show error message pop-up
  }
}

void FileSelection::chooseMapFile() {
  QString ret = QFileDialog::getOpenFileName(this,
          tr("Choose a Map File"), 
          QString::fromStdString(std::filesystem::current_path().parent_path().string()), // cha-cha-chain of FOO-OOLS
          tr("Map Files (*.map)"));
  if (!ret.isEmpty()) {
    std::filesystem::path map_file(ret.toStdString());
    setMapFile(map_file);
  }
}

void FileSelection::setMapFile(std::filesystem::path filepath) {
  try {
    if (scenario_service.setMapFile(filepath)) {
      // TODO: logic does not belong here. ask service for string to display.
      map_file_label->setText(filepath.filename().c_str());
      emit mapFileChanged();
    }
  } catch (const std::invalid_argument& e) {
    qDebug() << e.what();
  }
}

