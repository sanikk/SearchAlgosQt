#pragma once
#include "cell_flags.h"
#include "retval.h"
#include "scenario_service.h"

#include <vector>

#include <QObject>

/// Bitmask for leaving only the WALL/open bits from citymap.
constexpr std::uint8_t CLEAR_SCENARIO = WALL;
/// Bitmask for clearing fringe visit/expand bits from citymap.
constexpr std::uint8_t CLEAR_FRINGE = ~(VISIT_F | EXPAND_F);
/// Bitmask for clearing A* visit/expand bits from citymap
constexpr std::uint8_t CLEAR_ASTAR = ~(VISIT_A | EXPAND_A);

/// Manages searches and holds/manipulates the current map state.
class SearchService : public QObject {
  Q_OBJECT
public:
  SearchService(ScenarioService& i_scenario_service);
  void run_astar(int scenario_index);

  /// Runs fringe search on Scenario <index>.
  ///
  /// @param scenario_index the index of the scenario to run.
  void run_fringe(int scenario_index);
  void astar_full_run();
  void fringe_full_run();
  int full_comparison_run();
  void fringe_dll(int scenario_index);

  /// Returns an int vector showing the current map view.
  ///
  /// Each node on the map is represented by a single int for the visible color of that node.
  /// For use in VisualSearchTab.
  ///
  /// @param show_astar controls if astar markings show on current map view
  /// @param show_fringe controls if fringe markings show on current map view
  std::vector<int> get_map_frame(bool show_astar, bool show_fringe);

  std::vector<RetVal> run_astar_for_bucket(const int bucket);
  std::vector<RetVal> run_fringe_for_bucket(const int bucket);

  /// For running A* in VisualSearchTab.
  ///
  /// Runs A* in another thread, sends signals to SearchService.
  ///
  /// @param scenario_index index of Scenario to run.
  void run_astar_thread(const int scenario_index);
  void run_fringe_thread(const int scenario_index);

  std::vector<RetVal> run_test_version_for_bucket(const int bucket);
public slots:
  void visit_astar_slot(int x, int y);
  void expand_astar_slot(int x, int y);
  void found_astar_slot(RetVal ret);

  void visit_fringe_slot(int x, int y);
  void expand_fringe_slot(int x, int y);
  void found_fringe_slot(RetVal ret);

  /// Resets A* bits from citymap, resets A* counters to 0.
  void reset_astar();
  /// Resets fringe bits from citymap, resets fringe counters to 0.
  void reset_fringe();

signals:
  void visit_astar_signal(int x, int y);
  void expand_astar_signal(int x, int y);
  void found_astar_signal(RetVal ret);

  void visit_fringe_signal(int x, int y);
  void expand_fringe_signal(int x, int y);
  void found_fringe_signal(RetVal ret);

  void redraw_map();

private:
  ScenarioService& scenario_service;
  std::vector<uint8_t>& citymap;
  int astar_visits, astar_expands;
  int fringe_visits, fringe_expands;
  double fringe_cost, astar_cost, fringe_flimit;

  /// Loads the Scenario <scenario_index> to be current one.
  void load_scenario(const int index);

  /// Marks start and goal of given Scenario on the internal map representation.
  ///
  /// @param scenario the Scenario object to use
  void set_start_goal(Scenario& scenario);

  /// Clears all map info. You need to read a map from file after this.
  void clear_storage();


  /// Clears internal storage of scenario & search bits.
  ///
  /// Clears away bits 0-6. Only leaves the WALL/open bit set.
  void clear_scenario();


  /// Resets visited/expanded counters for the visual searches.
  void reset_counters();
};
