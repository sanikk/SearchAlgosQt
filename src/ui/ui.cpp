#include "ui.h"

Ui::Ui(ScenarioService scenario_service) {
  QVBoxLayout *mainLayout = new QVBoxLayout;

  // scenario_controls = new ScenarioControls{scenario_service};
  // mainLayout->addWidget(scenario_controls);
  tab_window = new TabWindow{scenario_service};
  mainLayout->addWidget(tab_window);
  // QPushButton *openfile = new QPushButton{"press me!"};
  // mainLayout->addWidget(openfile);
  setLayout(mainLayout);
  setWindowTitle("QT STARTER");
}


TabWindow::TabWindow(ScenarioService& scenario_service) {
  scenario_controls_tab = new ScenarioControls{scenario_service};
  addTab(scenario_controls_tab, "Scenario Controls");
  bucket_tab = new BucketTab{scenario_service};
  addTab(bucket_tab, "BucketTab");
}
