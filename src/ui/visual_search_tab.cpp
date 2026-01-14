#include "visual_search_tab.h"
#include "fullscreenDialog.h"
#include "search_service.h"
#include <qnamespace.h>

VisualSearchTab::VisualSearchTab(ScenarioService& i_scenario_service, SearchService& i_search_service, ScenarioControls* i_scenario_controls)
  : QWidget(), scenarioService(i_scenario_service), searchService(i_search_service), scenario_controls(i_scenario_controls) {
  
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

  mapScene = new MapWidget{};
  scroll = new QScrollArea;
  scroll->setWidget(mapScene);
  scroll->setWidgetResizable(false);
  tabLayout->addWidget(scroll);
  // view->setDragMode(QGraphicsView::ScrollHandDrag);
  // view->setRenderHint(QPainter::SmoothPixmapTransform, false);
  // view->setRenderHint(QPainter::Antialiasing, false);
  // view->setRenderHint(QPainter::LosslessImageRendering, false);

  setLayout(tabLayout);

  connect(fullscreenButton, &QPushButton::clicked, this, &VisualSearchTab::launchFullscreenDialog);
  connect(showHideFringeButton, &QPushButton::clicked, this, &VisualSearchTab::showHideFringe);
  connect(showHideAstarButton, &QPushButton::clicked, this, &VisualSearchTab::showHideAstar);
  connect(runAstarButton, &QPushButton::clicked, this, &VisualSearchTab::runAstar);

  connect(&searchService, &SearchService::astarVisit, mapScene, &MapWidget::astarVisit, Qt::DirectConnection);
  connect(&searchService, &SearchService::astarExpand, mapScene, &MapWidget::astarExpand, Qt::DirectConnection);
}


void VisualSearchTab::launchFullscreenDialog() {
  FullscreenDialog* fsd = new FullscreenDialog{scroll, scenario_controls};
  connect(fsd->runAstarButton, &QPushButton::clicked, runAstarButton, &QPushButton::clicked);
  connect(fsd->runFringeButton, &QPushButton::clicked, runFringeButton, &QPushButton::clicked);
  connect(fsd->showHideAstarButton, &QPushButton::clicked, showHideAstarButton, &QPushButton::clicked);
  connect(fsd->showHideFringeButton, &QPushButton::clicked, showHideFringeButton, &QPushButton::clicked);

  connect(fsd, &QDialog::finished, this, &VisualSearchTab::endFullScreenDialog);
  fsd->showFullScreen();
}

void VisualSearchTab::endFullScreenDialog() {
  scroll->setParent(this);
  tabLayout->addWidget(scroll);
  emit fullscreenDialogClosed();
}

void VisualSearchTab::mapChanged() {
  mapScene->setMap(scenarioService.get_map());
}

void VisualSearchTab::scenarioChanged(int index) {
  mapScene->setScenario(scenarioService.get_scenario(index));
}

void VisualSearchTab::showHideFringe() {
  mapScene->showHideFringe();
  if (mapScene->showFringe) {
    showHideFringeButton->setText("Hide Fringe");
  } else {
    showHideFringeButton->setText("Show Fringe");
  }
}

void VisualSearchTab::runFringe() {
  mapScene->start_search();
}


void VisualSearchTab::runAstar() {
  mapScene->start_search();
  searchService.run_astar_thread(scenario_controls->get_scenarioIndex());
}

void VisualSearchTab::showHideAstar() {
  mapScene->showHideAstar();
  if (mapScene->showAstar) {
    showHideAstarButton->setText("Hide A*");
  } else {
    showHideAstarButton->setText("Show A*");
  }
}
