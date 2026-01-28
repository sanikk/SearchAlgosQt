#include "testbed_tab.h"


TestBedTab::TestBedTab(ScenarioService& i_scenario_service, SearchService& i_search_service, ScenarioControls* i_scenario_controls) 
  : scenario_service(i_scenario_service), search_service(i_search_service), scenario_controls(i_scenario_controls) {
  QVBoxLayout *layout = new QVBoxLayout{};
  run_box = get_run_box();
  layout->addWidget(run_box);
  result_table = get_result_table();
  layout->addWidget(result_table);
  setLayout(layout);

  connect(test_button, &QPushButton::clicked, this, &TestBedTab::run_test);
  connect(base_button, &QPushButton::clicked, this, &TestBedTab::run_base);
}

QTableWidget* TestBedTab::get_result_table() {
  QTableWidget *table = new QTableWidget{this};
  table->setRowCount(10);
  QStringList labels({
    // scenario columns
    "id", "start", "goal", "cost",
    // A* columns
    "Test cost", "time",
    // fringe columns
    "Base cost", "time"
  });
  table->setColumnCount(labels.size());
  table->setHorizontalHeaderLabels(labels);
  return table; 
}

void TestBedTab::run_test() {
  // qDebug() << "running astar";
  try {
    int bucket = scenario_controls->get_bucket_index();
    if (bucket == -1) {
      return;
    }
    std::vector<RetVal> retvals = search_service.run_test_version_for_bucket(bucket);
    load_retvals_to_result_table(retvals, 4);
  } catch (std::runtime_error &e) {
    qDebug() << e.what();
  }
}

void TestBedTab::run_base() {
  try {
    int bucket = scenario_controls->get_bucket_index();
    if (bucket == -1) {
      qDebug() << "scenarioControl.get_bucketIndex return -1";
      return;
    }
    std::vector<RetVal> retvals = search_service.run_fringe_for_bucket(bucket);
    load_retvals_to_result_table(retvals, 6);
  } catch (std::runtime_error &e) {
    qDebug() << e.what();
  }
}

QWidget* TestBedTab::get_run_box() {
  QWidget *box = new QWidget{this};
  QHBoxLayout *boxLayout = new QHBoxLayout{};
  test_button = new QPushButton{"Run Test Version"};
  boxLayout->addWidget(test_button);
  base_button = new QPushButton{"Run Base Version"};
  boxLayout->addWidget(base_button);
  box->setLayout(boxLayout);
  return box;
}


void TestBedTab::update_table_scenarios(int index) {
  if (index==-1) {
    return;
  }
  result_table->clear();
  try {
    std::vector<Scenario> scenarioList = scenario_service.get_bucket_scenarios(index);
    for (int i=0; i < scenarioList.size(); i++) {
      Scenario scenario = scenarioList[i];
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

void TestBedTab::load_retvals_to_result_table(std::vector<RetVal> retvals, int startColumn) {
  for (int i=0; i < retvals.size(); i++) {
    if (retvals[i].cost.has_value()) {
      QTableWidgetItem *cost = new QTableWidgetItem{QString("%1").arg(retvals[i].cost.value())};
      result_table->setItem(i, startColumn , cost);
    }
    if (retvals[i].timing.has_value()) {
      QTableWidgetItem *timing = new QTableWidgetItem{QString("%1").arg(retvals[i].timing.value().count())};
      result_table->setItem(i, startColumn + 1, timing);
    }
  }
}

