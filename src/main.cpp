#include "scenario_service.h"
#include "search_service.h"
#include "ui.h"

#include <QApplication>


int main(int argc, char *argv[]) {
  ScenarioService scenario_service = ScenarioService();
  
  SearchService search_service(scenario_service);

  
  QApplication app = QApplication(argc, argv);

  Ui ui;
  ui.show();

  return app.exec();
}
