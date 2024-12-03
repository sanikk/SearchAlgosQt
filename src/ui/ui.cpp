#include "ui.h"
#include <QtWidgets>

Ui::Ui() {
  QVBoxLayout *mainLayout = new QVBoxLayout;

  scenario_controls = new ScenarioControls;
  mainLayout->addWidget(scenario_controls);

  QPushButton *openfile = new QPushButton{"press me!"};
  mainLayout->addWidget(openfile);
  setLayout(mainLayout);
  setWindowTitle("QT STARTER");
}
