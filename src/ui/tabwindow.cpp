#include "tabwindow.h"


TabWindow::TabWindow(ScenarioService& scenario_service) {
  scenario_controls_tab = new ScenarioControls{scenario_service};
  addTab(scenario_controls_tab, "Scenario Controls");
  bucket_tab = new BucketTab{scenario_service};
  addTab(bucket_tab, "BucketTab");
}
