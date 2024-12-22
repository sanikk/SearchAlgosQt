#include "linknode.h"
#include <unordered_map>

class LinkedPairMap {
  public:
    // fringe variables
    std::unordered_map<int, LinkNode*> fringe;
    std::unordered_map<int, LinkNode*>::iterator tail;
    std::unordered_map<int, LinkNode*>::iterator head;
    // actual functions
    LinkedPairMap(const int& start_value, const int& map_size);
    void add_tail(const int& value);
    void cut_links(const std::unordered_map<int, LinkNode*>::iterator& it);
    void remove_current(std::unordered_map<int, LinkNode*>::iterator& fringe_it);
    // convenience functions. remove these to lessen overhead.
    std::unordered_map<int, LinkNode*>::iterator begin() { return fringe.begin(); };
    std::unordered_map<int, LinkNode*>::iterator end() { return fringe.end(); };

    // work variables that will keep getting replaced
    //  private:
    std::unordered_map<int, LinkNode*>::iterator work_it;
    std::unordered_map<int, LinkNode*>::iterator left;
    std::unordered_map<int, LinkNode*>::iterator right;
};
