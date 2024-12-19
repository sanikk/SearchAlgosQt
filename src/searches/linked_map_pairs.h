#include <unordered_map>




struct LinkNode {

  std::unordered_map<int, LinkNode*>::iterator left;
  std::unordered_map<int, LinkNode*>::iterator right;
  int value;

  LinkNode(int i_value, std::unordered_map<int, LinkNode*>::iterator left={}, std::unordered_map<int, LinkNode*>::iterator right={}) 
    : value(i_value), left(left), right(right) {}
};


class LinkedMapPairs {
public:
  std::unordered_map<int, LinkNode*> fringe;
  LinkedMapPairs(int start);
  std::unordered_map<int, LinkNode*>::iterator head;
  std::unordered_map<int, LinkNode*>::iterator tail;
  void add_tail(int value);
  void remove_current(std::unordered_map<int, LinkNode*>::iterator it);
private:
  void cut_links(int value);
  void cut_links(std::unordered_map<int, LinkNode*>::iterator it);

// iterator constructor with default value equals .end(). Use .end() to compare against or default iterator will f u up!
};
