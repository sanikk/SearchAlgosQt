#pragma once
#include "models.h"
#include "tools.h"
#include "shared_search_tools.h"


struct Link {
  int value;
  Link* prev;
  Link* next;

  Link() : prev(nullptr), next(nullptr) {}
  Link(int i_value) : value(i_value), prev(nullptr), next(nullptr) {}
  Link(int i_value, Link* i_prev, Link* i_next) : value(i_value), prev(i_prev), next(i_next) {}
};

RetVal fringe_with_dll(int startx, int starty, int goalx, int goaly, std::vector<std::string> citymap);

