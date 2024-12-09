#include "search_tabs.h"

SearchTab::SearchTab(ScenarioService& i_scenario_service, SearchService& i_search_service, ScenarioControls& i_scenario_controls)
  : scenario_service(i_scenario_service), search_service(i_search_service), scenario_controls(i_scenario_controls) {
  
  QVBoxLayout *tabLayout = new QVBoxLayout{};
  setLayout(tabLayout);
}

FringeTab::FringeTab(ScenarioService& i_scenario_service, SearchService& i_search_service, ScenarioControls& i_scenario_controls)
: SearchTab(i_scenario_service, i_search_service, i_scenario_controls) {

}

AstarTab::AstarTab(ScenarioService& i_scenario_service, SearchService& i_search_service, ScenarioControls& i_scenario_controls)
: SearchTab(i_scenario_service, i_search_service, i_scenario_controls) {

}

