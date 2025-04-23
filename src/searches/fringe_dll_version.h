#pragma once
#include "scenario.h"
#include "retval.h"
// #include "tools.h"
// #include "shared_search_tools.h"
// #include "dll.h"
#include "heuristics.h"
#include "children.h"
#include "conversions.h"
#include "adjust.h"
#include <vector>
#include <string>
#include <unordered_map>

struct Link {
  int value;
  Link* prev;
  Link* next;

  Link() : prev(nullptr), next(nullptr) {}
  Link(int i_value, Link* i_prev=nullptr, Link* i_next=nullptr) : value(i_value), prev(i_prev), next(i_next) {}
};


RetVal fringe_with_dll(int startx, int starty, int goalx, int goaly, std::vector<std::string> citymap);

