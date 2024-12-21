#pragma once
#include <unordered_map>

struct LinkNode {

    std::unordered_map<int, LinkNode*>::iterator left;
    std::unordered_map<int, LinkNode*>::iterator right;
    int value;

    explicit LinkNode(int i_value, std::unordered_map<int, LinkNode*>::iterator left, std::unordered_map<int, LinkNode*>::iterator right)
        : value(i_value), left(left), right(right) {}
};

class LinkedMapPairs {
  public:
    std::unordered_map<int, LinkNode*> fringe;
    // LinkedMapPairs(int map_size);
    LinkedMapPairs(int start, int map_size);
    std::unordered_map<int, LinkNode*>::iterator head;
    std::unordered_map<int, LinkNode*>::iterator tail;
    void add_first(int value);
    void add_tail(int value);
    // void remove_current(std::unordered_map<int, LinkNode*>::iterator it,
    // std::unordered_map<int, LinkNode*>::iterator& fringe_it);
    void remove_current(std::unordered_map<int, LinkNode*>::iterator& fringe_it);
    std::unordered_map<int, LinkNode*>::iterator begin();
    std::unordered_map<int, LinkNode*>::iterator end();

  private:
    void cut_links(int value);
    void cut_links(std::unordered_map<int, LinkNode*>::iterator it);

    // iterator constructor with default value equals .end(). Use .end() to
    // compare against or default iterator will f u up!
};
