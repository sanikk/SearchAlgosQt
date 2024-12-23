#include "linked_map_pairs.h"
#include <iostream>

LinkedMapPairs::LinkedMapPairs(int start, int map_size) {
  LinkNode *start_node = new LinkNode{start};
  fringe = {{start, new LinkNode{start}}};
  fringe.reserve(map_size * map_size);
  auto it = fringe.begin();
  head = it;
  tail = it;
  it->second->left = fringe.end();
  it->second->right = fringe.end();

  end = fringe.end();
}

void LinkedMapPairs::add_tail(int value) {
  auto it = fringe.find(value);
  if (tail != it) {
    if (it != fringe.end()) {
      LinkNode *node = it->second;
      if (node->left != fringe.end() && node->right != fringe.end()) {
        node->left->second->right = node->right;
        node->right->second->left = node->left;
      } else if (node->left != fringe.end()) {
        node->left->second->right = fringe.end();
      } else if (node->right != fringe.end()) {
        node->right->second->left = fringe.end();
      }
      // else {
      //  std::cout << "this was the only node, no links to cut" << std::endl;
      // }
      if (head == it) {
        head = node->right;
      }
    } else {
      it = fringe.emplace(value, new LinkNode{value, tail}).first;
    }
    tail->second->right = it;
    tail = it;
  }
}

void LinkedMapPairs::remove_current(
    std::unordered_map<int, LinkNode *>::iterator &fringe_it) {
  std::unordered_map<int, LinkNode *>::iterator next_it =
      fringe_it->second->right;
  LinkNode *node = fringe_it->second;
  if (node->left != fringe.end() && node->right != fringe.end()) {
    node->left->second->right = node->right;
    node->right->second->left = node->left;
  } else if (node->left != fringe.end()) {
    node->left->second->right = fringe.end();
  } else if (node->right != fringe.end()) {
    node->right->second->left = fringe.end();
  }
  // else {
  //   std::cout << "this was the only node, no links to cut" << std::endl;
  // }
  if (head == fringe_it) {
    head = node->right;
  }
  if (tail == fringe_it) {
    tail = node->left;
  }
  delete fringe_it->second;
  fringe.erase(fringe_it);
  fringe_it = next_it;
}
