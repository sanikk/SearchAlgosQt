#include "scenario_service.h"
#include "search_service.h"
#include "ui.h"

#include <QApplication>


int main(int argc, char *argv[]) {
  QApplication app = QApplication(argc, argv);
  
  ScenarioService scenario_service;
  
  SearchService search_service(scenario_service);

  Ui ui(scenario_service, search_service);
  ui.show();

  return app.exec();
}
