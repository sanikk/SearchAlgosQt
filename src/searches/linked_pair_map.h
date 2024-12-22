#include "linknode.h"
#include <unordered_map>

class LinkedPairMap {
  public:
    std::unordered_map<int, LinkNode*> fringe;
    std::unordered_map<int, LinkNode*>::iterator work_it;
    std::unordered_map<int, LinkNode*>::iterator tail;
    std::unordered_map<int, LinkNode*>::iterator head;

    LinkedPairMap(const int& start_value, const int& map_size);
    void add_tail(const int& value);
    void cut_links(const std::unordered_map<int, LinkNode*>::iterator& it);
    void remove_current(std::unordered_map<int, LinkNode*>::iterator& fringe_it);

    std::unordered_map<int, LinkNode*>::iterator begin() { return fringe.begin(); };
    std::unordered_map<int, LinkNode*>::iterator end() { return fringe.end(); };
};
