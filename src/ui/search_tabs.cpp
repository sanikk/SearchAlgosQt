#include "search_tabs.h"
#include "scenario_service.h"
#include <QBoxLayout>
#include <QComboBox>

SearchTab::SearchTab(ScenarioService& i_scenario_service) : scenario_service(i_scenario_service) {
  QVBoxLayout *tabLayout = new QVBoxLayout{};
  setLayout(tabLayout);
}

FringeTab::FringeTab(ScenarioService& i_scenario_service) : SearchTab(i_scenario_service) {

}

AstarTab::AstarTab(ScenarioService& i_scenario_service) : SearchTab(i_scenario_service) {

}

