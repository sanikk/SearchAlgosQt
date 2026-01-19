#include "visual_search_tab.h"
#include "fullscreenDialog.h"
#include <qsizepolicy.h>

VisualSearchTab::VisualSearchTab(ScenarioService& i_scenario_service, SearchService& i_search_service, ScenarioControls* i_scenario_controls)
  : QWidget(), scenario_service(i_scenario_service), search_service(i_search_service), scenario_controls(i_scenario_controls) {
  
  tabLayout = new QVBoxLayout{};
  controlsBox = make_controls_box();
  controlsBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
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
  make_connections();
}

void VisualSearchTab::make_connections() {
  connect(fullscreenButton, &QPushButton::clicked, this, &VisualSearchTab::launchFullscreenDialog);
  connect(showHideFringeButton, &QPushButton::clicked, this, &VisualSearchTab::showHideFringe);
  connect(showHideAstarButton, &QPushButton::clicked, this, &VisualSearchTab::showHideAstar);
  connect(runAstarButton, &QPushButton::clicked, this, &VisualSearchTab::runAstar);
  connect(runFringeButton, &QPushButton::clicked, this, &VisualSearchTab::runFringe); 

  connect(&search_service, &SearchService::astarVisit, mapScene, &MapWidget::astarVisit, Qt::DirectConnection);
  connect(&search_service, &SearchService::astarExpand, mapScene, &MapWidget::astarExpand, Qt::DirectConnection);
  connect(&search_service, &SearchService::astarFound, mapScene, &MapWidget::astarFinished, Qt::DirectConnection);

  connect(&search_service, &SearchService::fringeVisit, mapScene, &MapWidget::fringeVisit, Qt::DirectConnection);
  connect(&search_service, &SearchService::fringeExpand, mapScene, &MapWidget::fringeExpand, Qt::DirectConnection);
  connect(&search_service, &SearchService::fringeFound, mapScene, &MapWidget::fringeFinished, Qt::DirectConnection);

  // TODO: example connection, just passing the current value as int to be displayed. SearchService keeps track of this.
  //connect(&search_service, &SearchService::astar_visited, astar_visited, &QLabel::setText);
}

QWidget* VisualSearchTab::make_controls_box() {

  controlsBox =new QWidget{};
  QVBoxLayout* controlsLayout = new QVBoxLayout;

  QHBoxLayout* buttonsLayout = make_buttons_row();
  controlsLayout->addLayout(buttonsLayout);
  QWidget* status_rows = make_status_rows();
  controlsLayout->addWidget(status_rows);

  controlsBox->setLayout(controlsLayout);
  return controlsBox;
}

QHBoxLayout* VisualSearchTab::make_buttons_row() {
  QHBoxLayout* buttonsLayout = new QHBoxLayout{};
  runFringeButton = new QPushButton{ "Run Fringe" };
  buttonsLayout->addWidget(runFringeButton);
  runAstarButton = new QPushButton{ "Run A*" };
  buttonsLayout ->addWidget(runAstarButton);
  showHideAstarButton = new QPushButton{"Hide A*"};
  buttonsLayout -> addWidget(showHideAstarButton);
  showHideFringeButton = new QPushButton{"Hide Fringe"};
  buttonsLayout -> addWidget(showHideFringeButton);
  fullscreenButton = new QPushButton{"Fullscreen"};
  buttonsLayout -> addWidget(fullscreenButton);
  return buttonsLayout;
}


QWidget* VisualSearchTab::make_status_rows() {
    // TODO: replace this bs setup with a QTableWidget & setCellWidget(label) in certain cells
    // that require updates. Then wire an int signal there, to cell::setText
    QWidget* status_rows = new QWidget{this};
    QGridLayout* status_layout = new QGridLayout;
  

    status_layout->addWidget(make_label("A*"), 0, 0);
    astar_visited  = make_label("visited: 0");
    status_layout->addWidget(astar_visited, 0, 1);
    astar_visited->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    astar_expanded = make_label("expanded: 0");
    astar_expanded->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    status_layout->addWidget(astar_expanded, 0, 2);
    astar_cost     = make_label("cost: 0");
    status_layout->addWidget(astar_cost, 0, 3);
    status_layout->addWidget(make_label("No limit"), 0, 4);
  

    status_layout->addWidget(make_label("Fringe"), 1, 0);
    fringe_visited  = make_label("visited: 0");
    status_layout->addWidget(fringe_visited, 1, 1);
    fringe_expanded = make_label("expanded: 0");
    status_layout->addWidget(fringe_expanded, 1, 2);
    fringe_cost     = make_label("cost: 0");
    status_layout->addWidget(fringe_cost, 1, 3);

    // TODO: make estimate here. wire heuristics through SearchService to give approximation of x1,y1 -> x2,y2
    fringe_flimit = make_label("Flimit: None");
    status_layout->addWidget(fringe_flimit, 1, 4);

    status_layout->setSpacing(0);
  
    status_rows->setLayout(status_layout);
    
    return status_rows;
}


QLabel* VisualSearchTab::make_label(QString text) {
    QLabel* label = new QLabel(text);
    label->setStyleSheet("border: 3px solid black; padding: 4px;");
    return label;
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
  mapScene->setMap(scenario_service.get_map());
}

void VisualSearchTab::scenarioChanged(int index) {
  mapScene->setScenario(scenario_service.get_scenario(index));
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
  search_service.run_fringe_thread(scenario_controls->get_scenarioIndex());
}


void VisualSearchTab::runAstar() {
  mapScene->start_search();
  search_service.run_astar_thread(scenario_controls->get_scenarioIndex());
}

void VisualSearchTab::showHideAstar() {
  mapScene->showHideAstar();
  if (mapScene->showAstar) {
    showHideAstarButton->setText("Hide A*");
  } else {
    showHideAstarButton->setText("Show A*");
  }
}

// TODO: ok this should all be in SearchService
void VisualSearchTab::visit_astar() {
    astar_visits++;
    astar_visited->setText(QString("visited: %1").arg(astar_visits));
}

void VisualSearchTab::expand_astar() {
    astar_expands++;
    astar_expanded->setText(QString("expanded: %1").arg(astar_expands));
}

void VisualSearchTab::cost_astar() {
    astar_costs++;
    astar_cost->setText(QString("costed: %1").arg(astar_costs));
}

void VisualSearchTab::visit_fringe() {
    fringe_visits++;
    fringe_visited->setText(QString("visited: %1").arg(fringe_visits));
}

void VisualSearchTab::expand_fringe() {
    fringe_expands++;
    fringe_expanded->setText(QString("expanded: %1").arg(fringe_expands));
}

void VisualSearchTab::cost_fringe() {
    fringe_costs++;
    fringe_cost->setText(QString("costed: %1").arg(fringe_costs));
}

void VisualSearchTab::reset_astar() {
    astar_visited->setText("visited: 0");
    astar_visits = 0;
    astar_expanded->setText("expanded: 0");
    astar_expands = 0;
    astar_cost->setText("cost: 0");
    astar_costs = 0;
}

void VisualSearchTab::reset_fringe() {
    fringe_visited->setText("visited: 0");
    fringe_visits = 0;
    fringe_expanded->setText("expanded: 0");
    fringe_expands = 0;
    fringe_cost->setText("cost: 0");
    fringe_costs = 0;
}
