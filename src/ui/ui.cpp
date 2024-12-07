#include "ui.h"
#include "scenario_controls.h"

Ui::Ui(ScenarioService scenario_service) {
  QVBoxLayout *mainLayout = new QVBoxLayout;

  scenario_controls = new ScenarioControls{scenario_service};
  mainLayout->addWidget(scenario_controls);
  tab_window = new QTabWidget{};
  mainLayout->addWidget(tab_window);

  file_selection_tab = new FileSelection{scenario_service};
  tab_window->addTab(file_selection_tab, "File Selection Tab");
  bucket_tab = new BucketTab{scenario_service};
  tab_window->addTab(bucket_tab, "Bucket Tab");
  astar_tab = new AstarTab{scenario_service};
  tab_window->addTab(astar_tab, "A* Tab");
  fringe_tab = new FringeTab{scenario_service};
  tab_window->addTab(fringe_tab, "Fringe Tab");
  
  setLayout(mainLayout);
  setWindowTitle("QT STARTER");

  connect(file_selection_tab, &FileSelection::scenarioFileChanged, scenario_controls, &ScenarioControls::updateBucketBox);
  connect(scenario_controls->bucket_box, &QComboBox::currentIndexChanged, bucket_tab, &BucketTab::updateTableScenarios);
}

