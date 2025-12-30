#include "fullscreenDialog.h"
#include "scenario_controls.h"


FullscreenDialog::FullscreenDialog(QScrollArea *scroll, ScenarioControls* i_scenario_controls) : QDialog(), scroll(scroll), scenario_controls(i_scenario_controls)
{
  setAttribute(Qt::WA_DeleteOnClose);
  QVBoxLayout *mainLayout = new QVBoxLayout{};
  mainLayout->addWidget(scenario_controls); 
  QWidget *controlsBox = new QWidget{};
  QHBoxLayout *boxLayout = new QHBoxLayout{};
  runAstarButton = new QPushButton{ "Run A*" };
  boxLayout->addWidget(runAstarButton);
  runFringeButton = new QPushButton{ "Run Fringe" };
  boxLayout->addWidget(runFringeButton);
  showHideAstarButton = new QPushButton{"Hide A*"};
  boxLayout->addWidget(showHideAstarButton);
  showHideFringeButton = new QPushButton{"Hide Fringe"};
  boxLayout->addWidget(showHideFringeButton);
  exitFullscreenButton = new QPushButton{"Exit fullscreen"};
  boxLayout->addWidget(exitFullscreenButton);
  controlsBox->setLayout(boxLayout);
  mainLayout->addWidget(controlsBox);
  mainLayout->addWidget(scroll);

  setLayout(mainLayout);
  
  connect(exitFullscreenButton, &QPushButton::clicked, this, &QDialog::close);
}
