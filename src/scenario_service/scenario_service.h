#pragma once
#include "scenario.h"
#include <vector>
#include <filesystem>

class ScenarioService {

public:
  ScenarioService(int width = 0, int height = 0);
  Scenario& get_scenario(const int index);
  std::vector<int> get_bucket_list();
  std::vector<Scenario> get_bucket_scenarios(int bucket);
  std::vector<uint8_t>& get_map();
  std::vector<Scenario> get_all_scenarios();
  bool set_map_file(const std::filesystem::path& i_map_file);
  bool set_scenario_file(const std::filesystem::path& i_scenario_file);
  std::tuple<int, int> get_map_size();
  int get_map_width() { return width; }
  void clear();

private:
  std::filesystem::path map_file;
  std::filesystem::path scenario_file;
  std::vector<Scenario> scenarios;
  std::vector<int> bucket_list;
  int width, height;

  std::vector<uint8_t> citymap;
};

