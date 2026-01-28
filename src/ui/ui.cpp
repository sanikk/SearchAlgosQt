#include "ui.h"

Ui::Ui(ScenarioService& i_scenario_service, SearchService& i_search_service) : scenario_controls(new ScenarioControls{i_scenario_service}) {
  main_layout = new QVBoxLayout;

  main_layout->addWidget(scenario_controls);
  tab_window = new QTabWidget{};
  main_layout->addWidget(tab_window);

  file_selection_tab = new FileSelection{i_scenario_service};
  tab_window->addTab(file_selection_tab, "File Selection Tab");
  bucket_tab = new BucketTab{i_scenario_service, i_search_service, scenario_controls};
  tab_window->addTab(bucket_tab, "Bucket Tab");
  visual_search_tab = new VisualSearchTab{i_scenario_service, i_search_service, scenario_controls};
  tab_window->addTab(visual_search_tab, "Search Tab");
  test_bed_tab = new TestBedTab{i_scenario_service, i_search_service, scenario_controls};
  tab_window->addTab(test_bed_tab, "TestBed Tab");
  setLayout(main_layout);
  setWindowTitle("SearchAlgosQt");

  connect(file_selection_tab, &FileSelection::scenario_file_changed, scenario_controls, &ScenarioControls::update_bucket_box);
  connect(scenario_controls->bucket_box, &QComboBox::currentIndexChanged, bucket_tab, &BucketTab::update_table_scenarios);
  connect(scenario_controls->bucket_box, &QComboBox::currentIndexChanged, test_bed_tab, &TestBedTab::update_table_scenarios);
  connect(file_selection_tab, &FileSelection::map_file_changed, visual_search_tab, &VisualSearchTab::map_changed);
  connect(scenario_controls, &ScenarioControls::scenario_changed, visual_search_tab, &VisualSearchTab::scenario_changed);
  connect(visual_search_tab, &VisualSearchTab::fullscreen_dialog_closed, this, &Ui::close_fullscreen_dialog);
}

void Ui::close_fullscreen_dialog() {
  scenario_controls->setParent(this);
  main_layout->insertWidget(0, scenario_controls);
}

