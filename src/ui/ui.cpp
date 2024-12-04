#include "ui.h"
#include <QtWidgets>

Ui::Ui(ScenarioService scenario_service) {
  QVBoxLayout *mainLayout = new QVBoxLayout;

  scenario_controls = new ScenarioControls{scenario_service};
  mainLayout->addWidget(scenario_controls);

  QPushButton *openfile = new QPushButton{"press me!"};
  mainLayout->addWidget(openfile);
  setLayout(mainLayout);
  setWindowTitle("QT STARTER");
}
