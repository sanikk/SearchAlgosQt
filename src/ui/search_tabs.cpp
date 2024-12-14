#include "search_tabs.h"

SearchTab::SearchTab(ScenarioService& i_scenario_service, SearchService& i_search_service)
  : scenario_service(i_scenario_service), search_service(i_search_service) {
  
  tabLayout = new QVBoxLayout{};
  controlsBox =new QWidget{};
  QHBoxLayout *controlsLayout = new QHBoxLayout{};
  runFringeButton = new QPushButton{ "Run Fringe" };
  controlsLayout->addWidget(runFringeButton);
  runAstarButton = new QPushButton{ "Run A*" };
  controlsLayout ->addWidget(runAstarButton);
  showHideAstarButton = new QPushButton{"Hide A*"};
  controlsLayout -> addWidget(showHideAstarButton);
  showHideFringeButton = new QPushButton{"Hide Fringe"};
  controlsLayout -> addWidget(showHideFringeButton);
  fullscreenButton = new QPushButton{"Fullscreen"};
  controlsLayout -> addWidget(fullscreenButton);

  controlsBox->setLayout(controlsLayout);
  tabLayout->addWidget(controlsBox);

  map_scene = new MapScene{};
  view = new QGraphicsView{ map_scene };
  view->setDragMode(QGraphicsView::ScrollHandDrag);
  view->scale(5, 5);
  tabLayout->addWidget(view);

  setLayout(tabLayout);

  connect(fullscreenButton, &QPushButton::clicked, this, &SearchTab::launchFullscreenDialog);
  connect(showHideFringeButton, &QPushButton::clicked, this, &SearchTab::showHideFringe);
  connect(showHideAstarButton, &QPushButton::clicked, this, &SearchTab::showHideAstar);
}


void SearchTab::launchFullscreenDialog() {
  FullscreenDialog* fsd = new FullscreenDialog{view};
  connect(fsd->runAstarButton, &QPushButton::clicked, runAstarButton, &QPushButton::clicked);
  connect(fsd->runFringeButton, &QPushButton::clicked, runFringeButton, &QPushButton::clicked);
  connect(fsd->showHideAstarButton, &QPushButton::clicked, showHideAstarButton, &QPushButton::clicked);
  connect(fsd->showHideFringeButton, &QPushButton::clicked, showHideFringeButton, &QPushButton::clicked);

  connect(fsd, &QDialog::finished, this, &SearchTab::endFullScreenDialog);
  fsd->showFullScreen();
}

void SearchTab::endFullScreenDialog() {
  view->setParent(this);
  tabLayout->addWidget(view);
}

void SearchTab::mapChanged() {
  map_scene->setMap(scenario_service.get_map());
}

void SearchTab::scenarioChanged(int index) {
  map_scene->setScenario(scenario_service.get_scenario(index));
}

void SearchTab::showHideFringe() {
  int ret = map_scene->showHideFringe();
  if (ret == 0) {
    return;
  }
  if (ret==1) {
    showHideFringeButton->setText("Hide Fringe");
    return;
  }
  if (ret==2) {
    showHideFringeButton->setText("Show Fringe");
    return;
  }
}

void SearchTab::showHideAstar() {
  int ret = map_scene->showHideAstar();
  if (ret==0) {
    return;
  }
  if (ret==1) {
    showHideAstarButton->setText("Hide A*");
    return;
  }
  if (ret==2) {
    showHideAstarButton->setText("Show A*");
    return;
  }
}
