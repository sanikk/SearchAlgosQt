#include "search_tabs.h"
#include "map_scene.h"
#include <qboxlayout.h>
#include <qpushbutton.h>
#include <qwidget.h>

SearchTab::SearchTab(ScenarioService& i_scenario_service, SearchService& i_search_service)
  : scenario_service(i_scenario_service), search_service(i_search_service) {
  
  QVBoxLayout *tabLayout = new QVBoxLayout{};
  QWidget *controlsBox =new QWidget{};
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

  connect(fullscreenButton, &QPushButton::clicked, view, &QGraphicsView::showFullScreen);
  connect(showHideFringeButton, &QPushButton::clicked, this, &SearchTab::showHideFringe);
  connect(showHideAstarButton, &QPushButton::clicked, this, &SearchTab::showHideAstar);
}

void SearchTab::mapChanged() {
  // view->setUpdatesEnabled(false);  // Disable updates temporarily
  map_scene->setMap(scenario_service.get_map());
  // view->setUpdatesEnabled(true);  // Disable updates temporarily
  // view->update();
}

void SearchTab::scenarioChanged(int index) {
  // view->setUpdatesEnabled(false);  // Disable updates temporarily
  map_scene->setScenario(scenario_service.get_scenario(index));
  // view->setUpdatesEnabled(true);  // Disable updates temporarily
  // view->update();
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
