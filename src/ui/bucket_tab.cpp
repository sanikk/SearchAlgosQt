#include "bucket_tab.h"

BucketTab::BucketTab(ScenarioService& i_scenario_service) : scenario_service(i_scenario_service) {
  QVBoxLayout *layout = new QVBoxLayout{};
  run_box = get_run_box();
  layout->addWidget(run_box);
  result_table = get_result_table();
  layout->addWidget(result_table);
  setLayout(layout);

  connect(astar_button, &QPushButton::clicked, this, &BucketTab::run_astar);
  connect(fringe_button, &QPushButton::clicked, this, &BucketTab::run_fringe);
}

QTableWidget* BucketTab::get_result_table() {
  QTableWidget *table = new QTableWidget{this};
  table->setRowCount(10);
  QStringList labels({
    // scenario columns
    "id", "start", "goal", "cost",
    // A* columns
    "A* cost", "time",
    // fringe columns
    "Fringe cost", "time"
  });
  table->setColumnCount(labels.size());
  table->setHorizontalHeaderLabels(labels);
  return table; 
}

void BucketTab::run_astar() {
  qDebug() << "running astar";
  
}

void BucketTab::run_fringe() {
  qDebug() << "running fringe";
}

QWidget* BucketTab::get_run_box() {
  QWidget *box = new QWidget{this};
  QHBoxLayout *box_layout = new QHBoxLayout{};
  astar_button = new QPushButton{"Run A*"};
  box_layout->addWidget(astar_button);
  fringe_button = new QPushButton{"Run Fringe"};
  box_layout->addWidget(fringe_button);
  box->setLayout(box_layout);
  return box;
}


void BucketTab::updateTableScenarios(int index) {
  if (index==-1) {
    return;
  }
  try {
    auto scenario_list = scenario_service.get_bucket_scenarios(index);
    for (int i=0; i < scenario_list.size(); i++) {
      Scenario scenario = scenario_list[i];
        QTableWidgetItem *id = new QTableWidgetItem{QString("%1").arg(scenario.id)};
        QTableWidgetItem *start = new QTableWidgetItem{QString("(%1 , %2)").arg(scenario.start_x).arg(scenario.start_y)};
        QTableWidgetItem *goal = new QTableWidgetItem{QString("(%1, %2)").arg(scenario.goal_x).arg(scenario.goal_y)};
        QTableWidgetItem *cost = new QTableWidgetItem{QString("%1").arg(scenario.cost)};
        result_table->setItem(i, 0, id);
        result_table->setItem(i, 1, start);
        result_table->setItem(i, 2, goal);
        result_table->setItem(i, 3, cost);
    }
  } catch (std::invalid_argument &e) {
    qDebug() << e.what();
  }
}

