#include "file_selection.h"

FileSelection::FileSelection(ScenarioService& i_scenario_service) : scenario_service(i_scenario_service) {
    QVBoxLayout *controlsLayout = new QVBoxLayout;

    scenario_file_label = new QLabel{tr("No Scenario File Chosen")};
    controlsLayout->addWidget(scenario_file_label);
    scenario_file_button = new QPushButton{"Choose a &Scenario file"};
    controlsLayout->addWidget(scenario_file_button);
    connect(scenario_file_button, &QPushButton::clicked, this, &FileSelection::choose_scenario_file);

    map_file_label = new QLabel{"No Map File Chosen"};
    controlsLayout->addWidget(map_file_label);
    map_file_button = new QPushButton{"Choose a &Map file"};
    controlsLayout->addWidget(map_file_button);
    connect(map_file_button, &QPushButton::clicked, this, &FileSelection::choose_map_file);

    setLayout(controlsLayout);
}

void FileSelection::choose_scenario_file() {
  QString ret = QFileDialog::getOpenFileName(this,
          tr("Choose a Scenario File"), 
          QString::fromStdString(std::filesystem::current_path().parent_path().string()), // cha-cha-chain of FOO-OOLS
          tr("Scenario Files (*.map.scen)"));
  if (!ret.isEmpty()) {
    std::filesystem::path scenario_file(ret.toStdString());
    set_scenario_file(scenario_file);
  }
}

void FileSelection::set_scenario_file(std::filesystem::path& filepath) {
  try {
    if (scenario_service.set_scenario_file(filepath)) {
      scenario_file_label->setText(QString::fromUtf8(filepath.filename().u8string().c_str()));
      std::filesystem::path candidate = filepath.replace_extension();
      if (!candidate.empty() && std::filesystem::is_regular_file(candidate)) {
        set_map_file(candidate);
      }
      emit scenario_file_changed();
    }
  } catch (const std::invalid_argument& e) {
    qDebug() << e.what();
    // TODO:show error message pop-up
  }
}

void FileSelection::choose_map_file() {
  QString ret = QFileDialog::getOpenFileName(this,
          tr("Choose a Map File"), 
          QString::fromStdString(std::filesystem::current_path().parent_path().string()), // cha-cha-chain of FOO-OOLS
          tr("Map Files (*.map)"));
  if (!ret.isEmpty()) {
    std::filesystem::path map_file(ret.toStdString());
    set_map_file(map_file);
  }
}

void FileSelection::set_map_file(std::filesystem::path& filepath) {
  try {
    if (scenario_service.set_map_file(filepath)) {
      map_file_label->setText(QString::fromUtf8(filepath.filename().u8string().c_str()));
      emit map_file_changed();
    }
  } catch (const std::invalid_argument& e) {
    qDebug() << e.what();
  }
}

