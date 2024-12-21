#include "travel_fringe.h"

std::vector<int> travel_fringe(LinkedMapPairs fringe) {
  std::vector<int> returnable;
  auto current = fringe.head;
  returnable.push_back(current->first);
  while (current != fringe.tail) {
    current = current->second->right;
    returnable.push_back(current->first);
  }
  return returnable;
}
