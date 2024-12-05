#include "bucket_tab.h"

BucketTab::BucketTab(const ScenarioService& i_scenario_service) : scenario_service(i_scenario_service) {
  QVBoxLayout *layout = new QVBoxLayout{};
  create_scenario_box();
  layout->addWidget(scenario_box);
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

void BucketTab::create_scenario_box() {
  scenario_box = new QGroupBox{};
  QVBoxLayout *box_layout = new QVBoxLayout{};
  result_table = get_result_table();
  box_layout->addWidget(result_table);
  scenario_box->setLayout(box_layout); 
}
