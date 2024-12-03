#pragma once
#include <unordered_map>
struct Link {
  int value;
  Link* prev;
  Link* next;

  Link() : prev(nullptr), next(nullptr) {}
  Link(int i_value) : value(i_value), prev(nullptr), next(nullptr) {}
  Link(int i_value, Link* i_prev, Link* i_next) : value(i_value), prev(i_prev), next(i_next) {}
};

class WrapperIterator {
  
  Link* current;

public:
  explicit WrapperIterator(Link* link) : current(link) {}

  int operator*() const { return current->value; }
  WrapperIterator& operator++() {
    current = current->next;
    return *this;
  }
  bool operator !=(const WrapperIterator& other) const { return current != other.current; }
};

class Fringe {
private:
  std::unordered_map<int, Link> links;
  Link* head;
  Link* tail;

public:
  Fringe();
  Fringe(int value);
  void add(int value);
  void remove(int value);
  bool empty();

  WrapperIterator begin() const {return WrapperIterator(head);}
  WrapperIterator end() const { return WrapperIterator(nullptr);}
  
};
