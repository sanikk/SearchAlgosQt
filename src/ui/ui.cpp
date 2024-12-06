#include "ui.h"

Ui::Ui(ScenarioService scenario_service) {
  QVBoxLayout *mainLayout = new QVBoxLayout;

  tab_window = new TabWindow{scenario_service};
  mainLayout->addWidget(tab_window);
  setLayout(mainLayout);
  setWindowTitle("QT STARTER");
}


TabWindow::TabWindow(ScenarioService& scenario_service) {
  file_selection_tab = new FileSelection{scenario_service};
  addTab(file_selection_tab, "Scenario Controls");
  bucket_tab = new BucketTab{scenario_service};
  addTab(bucket_tab, "BucketTab");
  astar_tab = new AstarTab{scenario_service};
  addTab(astar_tab, "A* Tab");
  fringe_tab = new FringeTab{scenario_service};
  addTab(fringe_tab, "Fringe Tab");
}
