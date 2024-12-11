#include "search_tabs.h"
#include <iostream>

SearchTab::SearchTab(ScenarioService& i_scenario_service, SearchService& i_search_service, ScenarioControls& i_scenario_controls)
  : scenario_service(i_scenario_service), search_service(i_search_service), scenario_controls(i_scenario_controls) {
  
  QVBoxLayout *tabLayout = new QVBoxLayout{};

  run_fringe_button = new QPushButton{ "Run Fringe Search" };
  tabLayout->addWidget(run_fringe_button);
  run_astar_button = new QPushButton{ "Run A* Search" };
  tabLayout ->addWidget(run_astar_button);
  
  map_scene = new MapScene{};
  view = new QGraphicsView{ map_scene };
  tabLayout->addWidget(view);

  setLayout(tabLayout);
}

void SearchTab::mapChanged() {
  // std::vector<std::string> citymap = scenario_service.get_map();
  std::cout << "setting map!" << std::endl;
  map_scene->setMap(scenario_service.get_map());
}
