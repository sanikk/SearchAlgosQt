

struct Link {
  int value;

  Link* prev;
  Link* next;

  Link() {};
  Link(int in_value) : value(in_value) {};
  Link(int in_value, Link* in_prev, Link* in_next) : value(in_value), prev(in_prev), next(in_next) {};

  
// methods
};

