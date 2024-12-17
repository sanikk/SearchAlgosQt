#include "fringe_with_dll.h"
#include <iostream>
#include <unordered_map>


// eli mappi tänne, ja linked list tänne. ei erillistä luokkaa.
// iteraattoria edistetään inline funktiolla, joka poistaa vanhan (linkit ja map-entry)
// ja siirtää fringe_it:n osoittamaan seuraavaan. Tämä rundin lopussa, ja tuossa väli-exitissä.
void fringe_add(int index, std::unordered_map<int, Link*> fringe_map, Link* fringe_head, Link* fringe_tail) {
  std::unordered_map<int, Link*>::iterator it = fringe_map.find(index);
  if (it == fringe_map.end()) {
    Link* new_node = new Link(index, fringe_tail, nullptr);
    fringe_map[index] = new_node;
    if (fringe_tail) fringe_tail->next = new_node;
    if (!fringe_head) fringe_head = new_node;
    fringe_tail = new_node;
  } else {
    Link* old_node = it->second;
    if (fringe_tail != old_node) {
      if (old_node->prev) old_node->prev->next = old_node->next;
      if (old_node->next) old_node->next->prev = old_node->prev;
      if (fringe_head == old_node) fringe_head = old_node->next;
      // old_node should be loose now, and head set to next node in line, or nullptr
      if (!fringe_head) fringe_head = old_node;
      if (fringe_tail) {
        fringe_tail->next = old_node;
        old_node->prev = fringe_tail;
      }
      fringe_tail = old_node;
    }
  }
}

RetVal fringe_with_dll(int startx, int starty, int goalx, int goaly, std::vector<std::string> citymap) {
  const int map_size = citymap.size();
  const int start_index = xy2int(startx, starty, map_size);
  // std::cout << "start_index: " << start_index << std::endl;
  const int goal_index = xy2int(goalx, goaly, map_size);
  // std::cout << "goal_index: " << goal_index << std::endl;
  
  // fringe setup:
  Link* fringe_head = new Link{start_index};
  Link* fringe_tail = fringe_head;
  std::unordered_map<int, Link*> fringe_map({{start_index, fringe_head}});


  //                                parent, cost_here
  std::unordered_map<int, std::tuple<int, double>> cache;
  cache[start_index] = {-1, 0.0};
  bool found = false;
  double foundcost;
  double flimit = float_adjust(heuristics(startx, starty, goalx, goaly));

  std::vector<std::tuple<int, int, double>> kids;

  while (!found && fringe_head != nullptr) {
    double fscore_min = 1000000;
    Link* fringe_it = fringe_head;

    while (fringe_it != nullptr) {
    // for(const int current: fringe) {
      const int current_index = fringe_it->value;
      const auto [currentx, currenty] = int2xy(current_index, map_size);
      const auto [parent, gscore] = cache[current_index];

      const double fscore = gscore + heuristics(currentx, currenty, goalx, goaly);

      std::cout << "current: " << current_index << ", (" << currentx << "," << currenty << "):" << gscore << std::endl;
      if (fscore > flimit) {
        fscore_min = std::min(fscore_min, fscore);
        // manually advance iterator
        fringe_it = fringe_it->next;
        continue;
      }

      if (current_index == goal_index) {
        std::cout << "goal found with cost " << gscore << std::endl;
        found = true;
        foundcost = gscore;
        break;
      }
      children(currentx, currenty, citymap, kids);
      for(const auto [childx, childy, childcost]: kids) {
        // std::cout << "child " <<childx << "," << childy << ":" << childcost << std::endl;
        const double child_gscore = gscore + childcost;
        const int child_index = xy2int(childx, childy, map_size);

        if (cache.find(child_index)!=cache.end()) {
          const auto [cached_parent, cached_gscore] = cache[child_index];
          if (child_gscore >= cached_gscore) {
            continue;
          }
        }
        std::unordered_map<int, Link*>::iterator it = fringe_map.find(current_index);
        if (it == fringe_map.end()) {
          Link* new_node = new Link(current_index, fringe_tail, nullptr);
          fringe_map[current_index] = new_node;
          if (fringe_tail) fringe_tail->next = new_node;
          if (!fringe_head) fringe_head = new_node;
          fringe_tail = new_node;
        } else {
          Link* old_node = it->second;
          if (fringe_tail != old_node) {
            if (old_node->prev) old_node->prev->next = old_node->next;
            if (old_node->next) old_node->next->prev = old_node->prev;
            if (fringe_head == old_node) fringe_head = old_node->next;
            // old_node should be loose now, and head set to next node in line, or nullptr
            if (!fringe_head) fringe_head = old_node;
            if (fringe_tail) {
              fringe_tail->next = old_node;
              old_node->prev = fringe_tail;
            }
            fringe_tail = old_node;
          }
        }
        // fringe_add(child_index, fringe_map, fringe_head, fringe_tail);
        cache[child_index] = {current_index, child_gscore};
      } // for the children
      kids.clear();
      // fringe_it = fringe_it->next;
      Link* next = fringe_it->next;
      if (fringe_it->prev) fringe_it->prev->next = fringe_it->next;
      if (fringe_it->next) fringe_it->next->prev = fringe_it->prev;
      if (fringe_head == fringe_it) fringe_head = fringe_it->next;
      if (fringe_tail == fringe_it) fringe_tail = fringe_it->prev;
      fringe_map.erase(fringe_it->value);
      delete fringe_it;
      fringe_it = next;

    } // for current : fringe
    flimit = float_adjust(fscore_min);
  } // while not found
  //
  //
  //
  //
  //
  //
  //
  //
  //
if (found) {
    std::vector<std::pair<int,int>> route;
    int current = goal_index;
    while (current != -1) {
      auto [cx, cy] = int2xy(current, map_size);
      route.push_back({cx,cy});
      // std::cout << cx << "," << cy << std::endl;
      current = std::get<0>(cache[current]);
    }
    return RetVal(foundcost, route);
  }
  return RetVal();
}
