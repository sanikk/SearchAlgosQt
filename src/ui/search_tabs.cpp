#include "search_tabs.h"
#include <iostream>

SearchTab::SearchTab(ScenarioService& i_scenario_service, SearchService& i_search_service)
  : scenario_service(i_scenario_service), search_service(i_search_service) {
  
  QVBoxLayout *tabLayout = new QVBoxLayout{};

  run_fringe_button = new QPushButton{ "Run Fringe Search" };
  tabLayout->addWidget(run_fringe_button);
  run_astar_button = new QPushButton{ "Run A* Search" };
  tabLayout ->addWidget(run_astar_button);
  
  map_scene = new MapScene{};
  view = new QGraphicsView{ map_scene };
  view->setDragMode(QGraphicsView::ScrollHandDrag);
  view->scale(10,10);
  tabLayout->addWidget(view);

  setLayout(tabLayout);
}

void SearchTab::mapChanged() {
  map_scene->setMap(scenario_service.get_map());
}

void SearchTab::scenarioChanged(int index) {
  map_scene->setScenario(scenario_service.get_scenario(index));
}
