#pragma once
#include "cell_flags.h"
#include "retval.h"
#include "scenario_service.h"

#include <vector>

#include <QObject>


constexpr std::uint8_t CLEAR_SCENARIO = WALL;
constexpr std::uint8_t CLEAR_FRINGE = ~(VISIT_F | EXPAND_F);
constexpr std::uint8_t CLEAR_ASTAR = ~(VISIT_A | EXPAND_A);

class SearchService : public QObject {
  Q_OBJECT
public:
  SearchService(ScenarioService& i_scenario_service);
  void run_astar(const int index);
  void run_fringe(int index);
  void astar_full_run();
  void fringe_full_run();
  int full_comparison_run();
  void fringe_dll(int scenario_id);

  std::vector<int> get_map_frame(bool show_astar, bool show_fringe);

  std::vector<RetVal> run_astar_for_bucket(const int bucket);
  std::vector<RetVal> run_fringe_for_bucket(const int bucket);

  void run_astar_thread(const int scenario_index);
  void run_fringe_thread(const int scenario_index);

  std::vector<RetVal> run_test_version_for_bucket(const int bucket);
public slots:
  void visit_astar_slot(int x, int y);
  void expand_astar_slot(int x, int y);
  void found_astar_slot(RetVal ret);
  void reset_astar();

  void visit_fringe_slot(int x, int y);
  void expand_fringe_slot(int x, int y);
  void found_fringe_slot(RetVal ret);
  void reset_fringe();

  void set_map();
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
  void load_scenario(const int index);

  int astar_visits, astar_expands;
  int fringe_visits, fringe_expands;
  double fringe_cost, astar_cost, fringe_flimit;

  std::vector<uint8_t>& citymap;

  void set_start_goal(Scenario& scenario);
  void clear_storage();
  void clear_scenario();
  void reset_counters();
};
