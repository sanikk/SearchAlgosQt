#pragma once
#include "scenario.h"
#include <vector>
#include <filesystem>

/// Handles the scenario and map info.
class ScenarioService {

public:
  ScenarioService(int width = 0, int height = 0);

  Scenario& get_scenario(int index);
  std::vector<Scenario> get_bucket_scenarios(int bucket);

  bool set_map_file(const std::filesystem::path& i_map_file);
  bool set_scenario_file(const std::filesystem::path& i_scenario_file);

  // Simple getters
  std::vector<Scenario> get_all_scenarios() { return scenarios; }
  std::vector<int> get_bucket_list() { return bucket_list; }
  std::vector<uint8_t>& get_map() { return citymap; }
  std::tuple<int, int> get_map_size() { return { width, height }; }
  int get_map_width() { return width; }
  
  /// Clears the saved citymap and scenarios.
  void clear();

private:
  std::filesystem::path map_file;
  std::filesystem::path scenario_file;
  std::vector<Scenario> scenarios;
  std::vector<int> bucket_list;
  int width, height;

  std::vector<uint8_t> citymap;
};

