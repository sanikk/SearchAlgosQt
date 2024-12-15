#include "ui.h"
#include "scenario_controls.h"
#include "testbed_tab.h"

Ui::Ui(ScenarioService& i_scenario_service, SearchService& i_search_service) : scenarioControls(new ScenarioControls{i_scenario_service}) {
  QVBoxLayout *mainLayout = new QVBoxLayout;

  mainLayout->addWidget(scenarioControls);
  tabWindow = new QTabWidget{};
  mainLayout->addWidget(tabWindow);

  fileSelectionTab = new FileSelection{i_scenario_service};
  tabWindow->addTab(fileSelectionTab, "File Selection Tab");
  bucketTab = new BucketTab{i_scenario_service, i_search_service, *scenarioControls};
  tabWindow->addTab(bucketTab, "Bucket Tab");
  visualSearchTab = new VisualSearchTab{i_scenario_service, i_search_service};
  tabWindow->addTab(visualSearchTab, "Search Tab");
  testBedTab = new TestBedTab{i_scenario_service, i_search_service, *scenarioControls};
  tabWindow->addTab(testBedTab, "TestBed Tab");
  setLayout(mainLayout);
  setWindowTitle("QT STARTER");

  connect(fileSelectionTab, &FileSelection::scenarioFileChanged, scenarioControls, &ScenarioControls::updateBucketBox);
  connect(scenarioControls->bucketBox, &QComboBox::currentIndexChanged, bucketTab, &BucketTab::updateTableScenarios);
  connect(scenarioControls->bucketBox, &QComboBox::currentIndexChanged, testBedTab, &TestBedTab::updateTableScenarios);
  connect(fileSelectionTab, &FileSelection::mapFileChanged, visualSearchTab, &VisualSearchTab::mapChanged);
  connect(scenarioControls, &ScenarioControls::scenarioChanged, visualSearchTab, &VisualSearchTab::scenarioChanged);
}

