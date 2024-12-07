#include "bucket_tab.h"

BucketTab::BucketTab(ScenarioService& i_scenario_service) : scenario_service(i_scenario_service) {
  QVBoxLayout *layout = new QVBoxLayout{};
  result_table = get_result_table();
  layout->addWidget(result_table);
  setLayout(layout);
}

QTableWidget* BucketTab::get_result_table() {
  QTableWidget *table = new QTableWidget{this};
  table->setRowCount(10);
  QStringList labels({
    // scenario columns
    "id", "bucket", "start", "goal", "cost",
    // A* columns
    "A* cost", "time",
    // fringe columns
    "Fringe cost", "time"
  });
  table->setColumnCount(labels.size());
  table->setHorizontalHeaderLabels(labels);
  return table; 
}



//  for (int i=0; i < bucket_scenarios.size() ; i++) {
//    auto fields = bucket_scenarios[i].get_fields();
//    for (int j=0; j < 6; j++) {
//      QTableWidgetItem *item = new QTableWidgetItem{};
//    }
//  }
//  for (Scenario &scen : bucket_scenarios) {
//    auto fields = scen.get_fields();
//    QTableWidgetItem *id = new QTableWidgetItem{std::get<0>(fields)};
//    QTableWidgetItem *start_x = new QTableWidgetItem{std::get<1>(fields)};
//    }
//  }


