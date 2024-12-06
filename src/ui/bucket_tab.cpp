#include "bucket_tab.h"

BucketTab::BucketTab(ScenarioService& i_scenario_service) : scenario_service(i_scenario_service), scenario_controls(new ScenarioControls{i_scenario_service}) {
  QVBoxLayout *layout = new QVBoxLayout{};
  layout->addWidget(scenario_controls);
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

