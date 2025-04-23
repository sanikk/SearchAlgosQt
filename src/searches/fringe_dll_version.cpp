#include "fringe_dll_version.h"
#include <iostream>


void add_child(std::unordered_map<int, Link*>& fringe_map, int child_index, Link*& fringe_head, Link*& fringe_tail) {
        std::unordered_map<int, Link*>::iterator it = fringe_map.find(child_index);
        Link* link;
        if (it == fringe_map.end()) {
          // std::cout << "adding new link to fringe!" << std::endl;
          link = new Link(child_index, fringe_tail, nullptr);
          fringe_map[child_index] = link;
        } else {
          // std::cout << "recycling old node" << std::endl;;
          link = it->second;
          if (link->prev) link->prev->next = link->next;
          if (link->next) link->next->prev = link->prev;
          if (fringe_head == link) fringe_head = link->next;
          if (fringe_tail == link) fringe_tail = link->prev; // maybe check for this and just pass things along?
          link->prev = fringe_tail;
        }
        // link should be loose now, fringe_head and fringe_tail set, and link has its prev set to fringe_tail
        if (fringe_tail) fringe_tail->next = link;
        fringe_tail = link;
        if (fringe_map[child_index] != link) {
          std::cout << "the link stored as value in fringe_map was not updated correctly" << std::endl;
        }
}

void remove_node_and_advance_iterator(Link*& fringe_it, Link*& fringe_head, Link*& fringe_tail, std::unordered_map<int, Link*>& fringe_map) {
      Link* next = fringe_it->next;
      if (fringe_it->prev) fringe_it->prev->next = fringe_it->next;
      if (fringe_it->next) fringe_it->next->prev = fringe_it->prev;
      if (fringe_head == fringe_it) fringe_head = fringe_it->next;
      if (fringe_tail == fringe_it) fringe_tail = fringe_it->prev;
      fringe_map.erase(fringe_it->value);
      delete fringe_it;

      fringe_it = next;
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
    // entä jos tää olis pointteri tohon key, value(Link*) pariin? aina edetessä otettais vaan Linkistä next.
    // hmm noi itse parit vois olla linkattuja sitten? no, v2 incoming.
    Link* fringe_it = fringe_head;

    while (fringe_it != nullptr) {
    // for(const int current: fringe) {
      const int current_index = fringe_it->value;
      const auto [currentx, currenty] = int2xy(current_index, map_size);
      const auto [parent, gscore] = cache[current_index];

      const double fscore = gscore + heuristics(currentx, currenty, goalx, goaly);

      std::cout << "current: " << current_index << ", (" << currentx << "," << currenty << "):" << gscore << std::endl;
      if (fscore > flimit) {
        // std::cout << fscore << " was over flimit " << flimit << std::endl;
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
          // std::cout << "cache hit!" << std::endl;
          const auto [cached_parent, cached_gscore] = cache[child_index];
          if (child_gscore >= cached_gscore) {
            // std::cout << "child gscore " << child_gscore << " was >= cached " << cached_gscore << std::endl;;
            continue;
          }
        }
        add_child(fringe_map, child_index, fringe_head, fringe_tail);
//        std::unordered_map<int, Link*>::iterator it = fringe_map.find(child_index);
//        if (it == fringe_map.end()) {
//          // std::cout << "adding new link to fringe!" << std::endl;
//          Link* new_node = new Link(child_index, fringe_tail, nullptr);
//          fringe_map[child_index] = new_node;
//          if (fringe_tail) fringe_tail->next = new_node;
//          if (!fringe_head) fringe_head = new_node;
//          fringe_tail = new_node;
//        } else {
//          // std::cout << "recycling old node" << std::endl;;
//          Link* old_node = it->second;
//          if (fringe_tail != old_node) {
//            if (old_node->prev) old_node->prev->next = old_node->next;
//            if (old_node->next) old_node->next->prev = old_node->prev;
//            if (fringe_head == old_node) fringe_head = old_node->next;
//            // old_node should be loose now, and head set to next node in line, or nullptr
//            if (!fringe_head) fringe_head = old_node;
//            if (fringe_tail) {
//              fringe_tail->next = old_node;
//              old_node->prev = fringe_tail;
//            }
//            fringe_tail = old_node;
//          }
//        }
        // fringe_add(child_index, fringe_map, fringe_head, fringe_tail);
        cache[child_index] = {current_index, child_gscore};
      } // for the children
      kids.clear();
      // fringe_it = fringe_it->next;
      remove_node_and_advance_iterator(fringe_it, fringe_head, fringe_tail, fringe_map);
//       Link* next = fringe_it->next;
//       if (fringe_it->prev) fringe_it->prev->next = fringe_it->next;
//       if (fringe_it->next) fringe_it->next->prev = fringe_it->prev;
//       if (fringe_head == fringe_it) fringe_head = fringe_it->next;
//       if (fringe_tail == fringe_it) fringe_tail = fringe_it->prev;
//       fringe_map.erase(fringe_it->value);
//       delete fringe_it;
//       fringe_it = next;

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
//7        Boston_0_512.map        512     512     236     132     247     163     35.55634918
//6        Boston_0_512.map	512	512	479	441	494	416	35.69848480
// int main(int argc, char* argv[]) {
//   std::vector<std::string> citymap = readMap("../../Boston_0_512.map", 4);
//   // fringe_with_dll(236, 132, 247, 163, citymap);
//   fringe_with_dll(479, 441, 494, 416, citymap);
// }
