#include "visual_search_tab.h"
#include "fullscreenDialog.h"

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


  astar_signals = new SearchSignals{};
  fringe_signals = new SearchSignals{};
  connect(astar_signals, &SearchSignals::visit, mapScene, &MapWidget::astarVisit);
  connect(astar_signals, &SearchSignals::finished, mapScene, &MapWidget::astarFinished);
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

// void VisualSearchTab::runAstar() {
// 
//   qDebug() << "running astar";
//   try {
//     // int bucket = scenario_controls->get_bucketIndex();
//     searchService.runAstarWithCallbacks(scenario_controls->get_scenarioIndex(),
//                                         signalAstarVisit,
//                                         signalAstarExpand);
//   } catch (std::runtime_error &e) {
//     qDebug() << e.what();
//   }
// }


void VisualSearchTab::runAstar() {
  //SearchSignals* astar_signals = new SearchSignals{};
  // connect(astar_signals, &SearchSignals::visit, mapScene, &MapWidget::astarVisit);
  // RetVal ret = searchService.runAstarWithSignals(scenario_controls->get_scenarioIndex(), astar_signals);
  searchService.runAstarWithSignals(scenario_controls->get_scenarioIndex(), astar_signals);
}

void VisualSearchTab::showHideAstar() {
  mapScene->showHideAstar();
  if (mapScene->showAstar) {
    showHideAstarButton->setText("Hide A*");
  } else {
    showHideAstarButton->setText("Show A*");
  }
}

// signal wrapper functions
// void VisualSearchTab::signalAstarVisit(int x, int y) {
//   emit astarVisitSignal(x, y); 
// }
// 
// void VisualSearchTab::signalAstarExpand(int x, int y) {
//   emit astarExpandSignal(x, y); 
// }
