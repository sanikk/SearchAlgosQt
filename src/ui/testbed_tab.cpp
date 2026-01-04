#include "testbed_tab.h"


TestBedTab::TestBedTab(ScenarioService& i_scenario_service, SearchService& i_search_service, ScenarioControls* i_scenario_controls) 
  : scenarioService(i_scenario_service), searchService(i_search_service), scenarioControls(i_scenario_controls) {
  QVBoxLayout *layout = new QVBoxLayout{};
  runBox = get_runBox();
  layout->addWidget(runBox);
  resultTable = get_resultTable();
  layout->addWidget(resultTable);
  setLayout(layout);

  connect(testButton, &QPushButton::clicked, this, &TestBedTab::runTest);
  connect(baseButton, &QPushButton::clicked, this, &TestBedTab::runBase);
}

QTableWidget* TestBedTab::get_resultTable() {
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

void TestBedTab::runTest() {
  // qDebug() << "running astar";
  try {
    int bucket = scenarioControls->get_bucketIndex();
    if (bucket == -1) {
      return;
    }
    std::vector<RetVal> retvals = searchService.runTestVersionForBucket(bucket);
    load_retvals_to_resultTable(retvals, 4);
  } catch (std::runtime_error &e) {
    qDebug() << e.what();
  }
}

void TestBedTab::runBase() {
  try {
    int bucket = scenarioControls->get_bucketIndex();
    if (bucket == -1) {
      qDebug() << "scenarioControl.get_bucketIndex return -1";
      return;
    }
    std::vector<RetVal> retvals = searchService.runFringeForBucket(bucket);
    load_retvals_to_resultTable(retvals, 6);
  } catch (std::runtime_error &e) {
    qDebug() << e.what();
  }
}

QWidget* TestBedTab::get_runBox() {
  QWidget *box = new QWidget{this};
  QHBoxLayout *boxLayout = new QHBoxLayout{};
  testButton = new QPushButton{"Run Test Version"};
  boxLayout->addWidget(testButton);
  baseButton = new QPushButton{"Run Base Version"};
  boxLayout->addWidget(baseButton);
  box->setLayout(boxLayout);
  return box;
}


void TestBedTab::updateTableScenarios(int index) {
  if (index==-1) {
    return;
  }
  resultTable->clear();
  try {
    std::vector<Scenario> scenarioList = scenarioService.get_bucketScenarios(index);
    for (int i=0; i < scenarioList.size(); i++) {
      Scenario scenario = scenarioList[i];
        QTableWidgetItem *id = new QTableWidgetItem{QString("%1").arg(scenario.id)};
        QTableWidgetItem *start = new QTableWidgetItem{QString("(%1 , %2)").arg(scenario.start_x).arg(scenario.start_y)};
        QTableWidgetItem *goal = new QTableWidgetItem{QString("(%1, %2)").arg(scenario.goal_x).arg(scenario.goal_y)};
        QTableWidgetItem *cost = new QTableWidgetItem{QString("%1").arg(scenario.cost)};
        resultTable->setItem(i, 0, id);
        resultTable->setItem(i, 1, start);
        resultTable->setItem(i, 2, goal);
        resultTable->setItem(i, 3, cost);
    }
  } catch (std::invalid_argument &e) {
    qDebug() << e.what();
  }
}

void TestBedTab::load_retvals_to_resultTable(std::vector<RetVal> retvals, int startColumn) {
  for (int i=0; i < retvals.size(); i++) {
    if (retvals[i].cost.has_value()) {
      QTableWidgetItem *cost = new QTableWidgetItem{QString("%1").arg(retvals[i].cost.value())};
      resultTable->setItem(i, startColumn , cost);
    }
    if (retvals[i].timing.has_value()) {
      QTableWidgetItem *timing = new QTableWidgetItem{QString("%1").arg(retvals[i].timing.value().count())};
      resultTable->setItem(i, startColumn + 1, timing);
    }
  }
}

