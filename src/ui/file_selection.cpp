#include "file_selection.h"

FileSelection::FileSelection(ScenarioService& i_scenario_service) : scenarioService(i_scenario_service) {
    QVBoxLayout *controlsLayout = new QVBoxLayout;

    scenarioFileLabel = new QLabel{tr("No Scenario File Chosen")};
    controlsLayout->addWidget(scenarioFileLabel);
    scenarioFileButton = new QPushButton{"Choose a &Scenario file"};
    controlsLayout->addWidget(scenarioFileButton);
    connect(scenarioFileButton, &QPushButton::clicked, this, &FileSelection::chooseScenarioFile);

    mapFileLabel = new QLabel{"No Map File Chosen"};
    controlsLayout->addWidget(mapFileLabel);
    mapFileButton = new QPushButton{"Choose a &Map file"};
    controlsLayout->addWidget(mapFileButton);
    connect(mapFileButton, &QPushButton::clicked, this, &FileSelection::chooseMapFile);

    setLayout(controlsLayout);
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

void FileSelection::setScenarioFile(std::filesystem::path& filepath) {
  try {
    // TODO: ok this logic is in the wrong place. ask scenarioService for strings to display.
    if (scenarioService.setScenarioFile(filepath)) {
      scenarioFileLabel->setText(filepath.filename().c_str());
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

void FileSelection::setMapFile(std::filesystem::path& filepath) {
  try {
    if (scenarioService.setMapFile(filepath)) {
      // TODO: logic does not belong here. ask service for string to display.
      mapFileLabel->setText(filepath.filename().c_str());
      emit mapFileChanged();
    }
  } catch (const std::invalid_argument& e) {
    qDebug() << e.what();
  }
}

