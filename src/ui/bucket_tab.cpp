#include "bucket_tab.h"
#include <qlogging.h>
#include <qtablewidget.h>
#include <stdexcept>

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
        // QTableWidgetItem *cost = new QTableWidgetItem{QString("%1").arg(scenario.cost, 0, 'g', 4)};
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

