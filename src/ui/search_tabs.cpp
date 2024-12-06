#include "search_tabs.h"
#include "scenario_service.h"
#include <qboxlayout.h>
#include <qcombobox.h>
#include <qlogging.h>

SearchTab::SearchTab(ScenarioService& i_scenario_service) : scenario_service(i_scenario_service), scenario_controls(new ScenarioControls{i_scenario_service}) {
  QVBoxLayout *tabLayout = new QVBoxLayout{};
  tabLayout->addWidget(scenario_controls);
  setLayout(tabLayout);
}

FringeTab::FringeTab(ScenarioService& i_scenario_service) : SearchTab(i_scenario_service) {

}

AstarTab::AstarTab(ScenarioService& i_scenario_service) : SearchTab(i_scenario_service) {

}

ScenarioControls::ScenarioControls(ScenarioService& i_scenario_service) : scenario_service(i_scenario_service) {
  QVBoxLayout *controlsLayout = new QVBoxLayout{};
  bucket_box = new QComboBox{};
  controlsLayout->addWidget(bucket_box);
  scenario_box = new QComboBox{};
  controlsLayout->addWidget(scenario_box);
  setLayout(controlsLayout);
}
