#include "visual_search_tab.h"

VisualSearchTab::VisualSearchTab(ScenarioService& i_scenario_service, SearchService& i_search_service, ScenarioControls* i_scenario_controls)
  : QWidget(), scenario_service(i_scenario_service), search_service(i_search_service), scenario_controls(i_scenario_controls), show_astar(true), show_fringe(true)
{
  
  tab_layout = new QVBoxLayout{};
  controls_box = make_controls_box();
  controls_box->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  tab_layout->addWidget(controls_box);

  map_scene = new MapWidget{};
  scroll = new QScrollArea;
  scroll->setWidget(map_scene);
  scroll->setWidgetResizable(false);
  tab_layout->addWidget(scroll);
  // view->setDragMode(QGraphicsView::ScrollHandDrag);
  // view->setRenderHint(QPainter::SmoothPixmapTransform, false);
  // view->setRenderHint(QPainter::Antialiasing, false);
  // view->setRenderHint(QPainter::LosslessImageRendering, false);

  setLayout(tab_layout);
  make_connections();
}

void VisualSearchTab::make_connections() {
  connect(fullscreen_button, &QPushButton::clicked, this, &VisualSearchTab::launchFullscreenDialog);
  connect(show_hide_fringe_button, &QPushButton::clicked, this, &VisualSearchTab::showHideFringe);
  connect(show_hide_astar_button, &QPushButton::clicked, this, &VisualSearchTab::showHideAstar);
  connect(run_astar_button, &QPushButton::clicked, this, &VisualSearchTab::runAstar);
  connect(run_fringe_button, &QPushButton::clicked, this, &VisualSearchTab::runFringe); 

//  connect(&search_service, &SearchService::visit_astar_signal, map_scene, &MapWidget::astarVisit, Qt::DirectConnection);
//  connect(&search_service, &SearchService::expand_astar_signal, map_scene, &MapWidget::astarExpand, Qt::DirectConnection);
//  connect(&search_service, &SearchService::found_astar_signal, map_scene, &MapWidget::astarFinished, Qt::DirectConnection);

//  connect(&search_service, &SearchService::visit_fringe_signal, map_scene, &MapWidget::fringeVisit, Qt::DirectConnection);
//  connect(&search_service, &SearchService::expand_fringe_signal, map_scene, &MapWidget::fringeExpand, Qt::DirectConnection);
//  connect(&search_service, &SearchService::found_fringe_signal, &MapWidget::fringeFinished, Qt::DirectConnection);

  // TODO: example connection, just passing the current value as int to be displayed. SearchService keeps track of this.
  //connect(&search_service, &SearchService::astar_visited, astar_visited, &QLabel::setText);
}

QWidget* VisualSearchTab::make_controls_box() {

  controls_box =new QWidget{};
  QVBoxLayout* controlsLayout = new QVBoxLayout;

  QHBoxLayout* buttonsLayout = make_buttons_row();
  controlsLayout->addLayout(buttonsLayout);
  QWidget* status_rows = make_status_rows();
  controlsLayout->addWidget(status_rows);

  controls_box->setLayout(controlsLayout);
  return controls_box;
}

QHBoxLayout* VisualSearchTab::make_buttons_row() {
  QHBoxLayout* buttonsLayout = new QHBoxLayout{};
  run_fringe_button = new QPushButton{ "Run Fringe" };
  buttonsLayout->addWidget(run_fringe_button);
  run_astar_button = new QPushButton{ "Run A*" };
  buttonsLayout ->addWidget(run_astar_button);
  show_hide_astar_button = new QPushButton{"Hide A*"};
  buttonsLayout -> addWidget(show_hide_astar_button);
  show_hide_fringe_button = new QPushButton{"Hide Fringe"};
  buttonsLayout -> addWidget(show_hide_fringe_button);
  fullscreen_button = new QPushButton{"Fullscreen"};
  buttonsLayout -> addWidget(fullscreen_button);
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
  fsd = new FullscreenDialog{scroll, scenario_controls};
  connect(fsd->run_astar_button, &QPushButton::clicked, run_astar_button, &QPushButton::clicked);
  connect(fsd->run_fringe_button, &QPushButton::clicked, run_fringe_button, &QPushButton::clicked);
  connect(fsd->show_hide_astar_button, &QPushButton::clicked, show_hide_astar_button, &QPushButton::clicked);
  connect(fsd->show_hide_fringe_button, &QPushButton::clicked, show_hide_fringe_button, &QPushButton::clicked);

  connect(fsd, &QDialog::finished, this, &VisualSearchTab::endFullScreenDialog);
  fsd->showFullScreen();
}

void VisualSearchTab::endFullScreenDialog() {
  scroll->setParent(this);
  tab_layout->addWidget(scroll);
  emit fullscreen_dialog_closed();
}


void VisualSearchTab::redraw_map() {
  // TODO: redraw_map AND mapChanged?
  map_scene->render_map(search_service.get_map_frame(show_astar, show_fringe), 
                      scenario_service.get_map_width());
}


void VisualSearchTab::map_changed() {
  map_scene->render_map(search_service.get_map_frame(show_astar, show_fringe), scenario_service.get_map_width());
}

void VisualSearchTab::scenario_changed(int index) {
  map_scene->render_map(search_service.get_map_frame(show_astar, show_fringe), scenario_service.get_map_width());
}

void VisualSearchTab::showHideFringe() {
  if (show_fringe) {
    show_hide_fringe_button->setText("Hide Fringe");
    if (fsd) {
      fsd->show_hide_fringe_button->setText("Hide Fringe");
    }
  } else {
    show_hide_fringe_button->setText("Show Fringe");
    if (fsd) {
      fsd->show_hide_fringe_button->setText("Show Fringe");
    }
  }
}

void VisualSearchTab::runFringe() {
  map_scene->start_search();
  search_service.run_fringe_thread(scenario_controls->get_scenario_index());
}


void VisualSearchTab::runAstar() {
  map_scene->start_search();
  search_service.run_astar_thread(scenario_controls->get_scenario_index());
}

void VisualSearchTab::showHideAstar() {
  if (show_astar) {
    show_hide_astar_button->setText("Hide A*");
    if (fsd) {
      fsd->show_hide_astar_button->setText("Hide A*");
    }
  } else {
    show_hide_astar_button->setText("Show A*");
    if (fsd) {
      fsd->show_hide_astar_button->setText("Show A*");
    }
  }
}

void VisualSearchTab::visit_astar(int x, int y, int value) {
  astar_visited->setText(QString("visited: %1").arg(value));
  if (show_astar) {
    map_scene->draw_pixel(x, y, 6);
  }
}

void VisualSearchTab::expand_astar(int x, int y, int value) {
  astar_expanded->setText(QString("expanded: %1").arg(value));
  if (show_astar) {
    map_scene->draw_pixel(x, y, 7);
  }
}

void VisualSearchTab::found_astar(RetVal ret) {
  if (ret.cost.has_value()) { 
    astar_cost->setText(QString("cost: %1").arg(ret.cost.value()));
  } else {
    astar_cost->setText("Not found");
  }
}

void VisualSearchTab::visit_fringe(int x, int y, int value) {
    fringe_visited->setText(QString("visited: %1").arg(value));
}

void VisualSearchTab::expand_fringe(int value) {
    fringe_expanded->setText(QString("expanded: %1").arg(value));
}

void VisualSearchTab::found_fringe(RetVal ret) {
  if (ret.cost.has_value()) { 
    fringe_cost->setText(QString("cost: %1").arg(ret.cost.value()));
  } else {
    fringe_cost->setText("Not found");
  }
}

void VisualSearchTab::reset_astar() {
    astar_visited->setText("visited: 0");
    astar_expanded->setText("expanded: 0");
    astar_cost->setText("cost: 0");
}

void VisualSearchTab::reset_fringe() {
    fringe_visited->setText("visited: 0");
    fringe_expanded->setText("expanded: 0");
    fringe_cost->setText("cost: 0");
}
