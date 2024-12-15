#include "visual_search_tab.h"

VisualSearchTab::VisualSearchTab(ScenarioService& i_scenario_service, SearchService& i_search_service)
  : QWidget(), scenarioService(i_scenario_service), searchService(i_search_service) {
  
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

  mapScene = new MapScene{};
  view = new QGraphicsView{ mapScene };
  view->setDragMode(QGraphicsView::ScrollHandDrag);
  view->scale(5, 5);
  tabLayout->addWidget(view);

  setLayout(tabLayout);

  connect(fullscreenButton, &QPushButton::clicked, this, &VisualSearchTab::launchFullscreenDialog);
  connect(showHideFringeButton, &QPushButton::clicked, this, &VisualSearchTab::showHideFringe);
  connect(showHideAstarButton, &QPushButton::clicked, this, &VisualSearchTab::showHideAstar);
}


void VisualSearchTab::launchFullscreenDialog() {
  FullscreenDialog* fsd = new FullscreenDialog{view};
  connect(fsd->runAstarButton, &QPushButton::clicked, runAstarButton, &QPushButton::clicked);
  connect(fsd->runFringeButton, &QPushButton::clicked, runFringeButton, &QPushButton::clicked);
  connect(fsd->showHideAstarButton, &QPushButton::clicked, showHideAstarButton, &QPushButton::clicked);
  connect(fsd->showHideFringeButton, &QPushButton::clicked, showHideFringeButton, &QPushButton::clicked);

  connect(fsd, &QDialog::finished, this, &VisualSearchTab::endFullScreenDialog);
  fsd->showFullScreen();
}

void VisualSearchTab::endFullScreenDialog() {
  view->setParent(this);
  tabLayout->addWidget(view);
}

void VisualSearchTab::mapChanged() {
  mapScene->setMap(scenarioService.get_map());
}

void VisualSearchTab::scenarioChanged(int index) {
  mapScene->setScenario(scenarioService.get_scenario(index));
}

void VisualSearchTab::showHideFringe() {
  int ret = mapScene->showHideFringe();
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

void VisualSearchTab::showHideAstar() {
  int ret = mapScene->showHideAstar();
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
