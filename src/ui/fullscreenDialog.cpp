#include "fullscreenDialog.h"


FullscreenDialog::FullscreenDialog(QScrollArea *scroll, ScenarioControls* i_scenario_controls) : QDialog(), scroll(scroll), scenario_controls(i_scenario_controls)
{
  setAttribute(Qt::WA_DeleteOnClose);
  QVBoxLayout *main_layout = new QVBoxLayout{};
  main_layout->addWidget(scenario_controls);

  QWidget *controls_box = new QWidget{};
  QHBoxLayout *box_layout = new QHBoxLayout{};
  run_astar_button = new QPushButton{ "Run A*" };
  box_layout->addWidget(run_astar_button);
  run_fringe_button = new QPushButton{ "Run Fringe" };
  box_layout->addWidget(run_fringe_button);
  show_hide_astar_button = new QPushButton{"Hide A*"};
  box_layout->addWidget(show_hide_astar_button);
  show_hide_fringe_button = new QPushButton{"Hide Fringe"};
  box_layout->addWidget(show_hide_fringe_button);
  exit_fullscreen_button = new QPushButton{"Exit fullscreen"};
  box_layout->addWidget(exit_fullscreen_button);
  controls_box->setLayout(box_layout);
  main_layout->addWidget(controls_box);

  main_layout->addWidget(scroll);

  setLayout(main_layout);
  
  connect(exit_fullscreen_button, &QPushButton::clicked, this, &QDialog::close);
}
