#include "ui.h"

Ui::Ui(ScenarioService scenario_service) {
  QVBoxLayout *mainLayout = new QVBoxLayout;

  tab_window = new TabWindow{scenario_service};
  mainLayout->addWidget(tab_window);
  setLayout(mainLayout);
  setWindowTitle("QT STARTER");
}


TabWindow::TabWindow(ScenarioService& scenario_service) {
  scenario_controls_tab = new ScenarioControls{scenario_service};
  addTab(scenario_controls_tab, "Scenario Controls");
  bucket_tab = new BucketTab{scenario_service};
  addTab(bucket_tab, "BucketTab");
  astar_tab = new AstarTab{scenario_service};
  addTab(astar_tab, "A* Tab");
  fringe_tab = new FringeTab{scenario_service};
  addTab(fringe_tab, "Fringe Tab");
}
