#include "search_tabs.h"
#include "scenario_service.h"
#include <qboxlayout.h>
#include <qcombobox.h>
#include <qlogging.h>

SearchTab::SearchTab(const ScenarioService& i_scenario_service) : scenario_service(i_scenario_service) {
  QVBoxLayout *tabLayout = new QVBoxLayout{};
  create_common_area();
  tabLayout->addWidget(common_area);
  setLayout(tabLayout);
}

void SearchTab::create_common_area() {
  common_area = new QWidget{};
  QVBoxLayout *common_areaLayout = new QVBoxLayout{};
  bucket_box = new QComboBox{};
  common_areaLayout->addWidget(bucket_box);
  scenario_box = new QComboBox{};
  common_areaLayout->addWidget(scenario_box);
  common_area->setLayout(common_areaLayout);
  qDebug() << "common area setup!";
}



FringeTab::FringeTab(const ScenarioService& i_scenario_service) : SearchTab(i_scenario_service) {

}

AstarTab::AstarTab(const ScenarioService& i_scenario_service) : SearchTab(i_scenario_service) {

}
