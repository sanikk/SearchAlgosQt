#pragma once
#include "node.h"
#include <cmath>

const double DIFF = std::sqrt(2.0) - 2.0;

double heuristics(int nodex, int nodey, int goalx, int goaly);
double heuristics(Node node, Node goal);



