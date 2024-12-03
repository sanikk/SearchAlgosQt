#include "dll.h"

Fringe::Fringe():head(nullptr), tail(nullptr) {}
Fringe::Fringe(int value):head(nullptr), tail(nullptr) {
    links.emplace(value, Link(value, tail, nullptr));
    head = &links[value];
    tail = &links[value];
  }

void Fringe::add(int value) {
    // no recycling version
    if (links.find(value) != links.end()) {
      remove(value);
    }
    links.emplace(value, Link(value, tail, nullptr));
    if (head == nullptr) {
        head = &links[value];
    }
    if (tail != nullptr) {
      tail->next = &links[value];
    }
    tail = &links[value];
  };


void Fringe::remove(int value) {
    Link& link = links[value];
    if (link.next != nullptr) {
        link.next->prev = link.prev;
    }
    if (link.prev != nullptr) {
        link.prev->next = link.next;
    }
    if (head == &link) {
        head = link.next;
    }
    if (tail == &link) {
        tail = link.prev;
    }
    links.erase(value);
}

bool Fringe::empty() {
    if (head == nullptr) {
        return true;
    }
    return false;
}

