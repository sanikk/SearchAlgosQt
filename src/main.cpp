#include "scenario_service/scenario_service.h"
#include "search_service.h"
#include "ui.h"
#include <iostream>
#include <ostream>
#include <string>
#include <cstring>
#include <tuple>

#include <QApplication>


void show_help() {
  std::cout << "Little search prog" << std::endl;
  std::cout << "This is very out of date now. check source for now." << std::endl;
  std::cout << "<prog> <search> <map_file> <scenario_identifier>" << std::endl;
  std::cout << "<prog> astar \"map_file\" bucket index" << std::endl;
  std::cout << "<prog> fringe \"map_file\" bucket index" << std::endl;
  std::cout << "<prog> astar \"map_file\" index" << std::endl;
  std::cout << "<prog> fringe \"map_file\" bucket index" << std::endl;
  std::cout << "<prog> fringe \"map file\" all - run all scenarios" << std::endl;
  std::cout << "please give a valid .map file as second argument. The .map.scen" << std::endl;
  std::cout << "file is also needed." << std::endl;
}

int getCommand(const std::string& cmd) {
  if (cmd == "astar") return 1;
  if (cmd == "fringe") return 2;
  if (cmd == "fullcomp") return 3;
  if (cmd == "frunge") return 5;
  if (cmd == "dll") return 6;
  if (cmd == "children") return 9;
  return -1;
}

int start_gui(int argc, char *argv[]) {
  QApplication app = QApplication(argc, argv);

  Ui ui;
  ui.show();

  return app.exec();
}

int main(int argc, char *argv[]) {
  ScenarioService scenario_service;
  if (argc > 2) {
    scenario_service = ScenarioService(argv[2]);
 
  } else {
    scenario_service = ScenarioService();
  }
  SearchService search_service(scenario_service);
  if (argc == 1) {
    return start_gui(argc, argv);
  }
  if (argc > 2) {
    switch (getCommand(argv[1])) {
      case 1: // astar
        if (argc == 3 && std::strcmp("all", argv[3]) == 0) {
          search_service.astar_full_run();
          return 0;
        }
        if (argc == 5) {
          search_service.run_astar(std::stoi(argv[3]), std::stoi(argv[4]));
          return 0;
        }
        if (argc == 4) {
          search_service.run_astar(std::stoi(argv[3]));
          return 0;
        
        show_help();
        return 1;
      
      case 2: // fringe

        if (argc == 3 && std::strcmp("all", argv[3]) == 0) {
          search_service.fringe_full_run();
          return 0;
        }
        if (argc == 5) {
          search_service.run_fringe(std::stoi(argv[3]), std::stoi(argv[4]));
          return 0;
        } 
        if (argc == 4) {
          search_service.run_fringe(std::stoi(argv[3]));
          return 0;
        }
        show_help();
        return 1;
        }
      case 3: // full comparison
        // search_service.full_comparison_run();
        return 1;

      case 5: // unoptimized fringe
        // search_service.fringe_unopt(std::stoi(argv[3]));
        return 1;

      case 6:
        search_service.fringe_dll(std::stoi(argv[3]));
        return 0;
      case 9: // children
        {
        std::vector<std::tuple<int, int, double>> node_list;
        children(std::stoi(argv[3]), std::stoi(argv[4]), scenario_service.get_map(), node_list);
        for (auto tup : node_list) {
          std::cout << std::get<0>(tup) << "," << std::get<1>(tup) << "," << std::get<2>(tup) << std::endl;
        }
        return 0; 
        }
      default:
          show_help();
          return 1;
    
    }
  }
}
