#include "linked_map_pairs.h"
#include <iostream>



LinkedMapPairs::LinkedMapPairs(int start, int map_size) 
{
    LinkNode* start_node = new LinkNode{start};
    fringe = {{start, new LinkNode{start}}};
    fringe.reserve(map_size * map_size);
    auto it = fringe.begin();
    head = it;
    tail = it;;
    end = fringe.end();
}


void LinkedMapPairs::add_tail(int value) {
    auto it = fringe.find(value);
    if (it != fringe.end()) {
        cut_links(it);
        delete it->second;
        fringe.erase(it);
    }
    auto new_it = fringe.emplace(value, new LinkNode{value, tail});
    tail->second->right = new_it.first;
    tail = new_it.first;

}

void LinkedMapPairs::remove_current(std::unordered_map<int, LinkNode*>::iterator& fringe_it) {
    std::unordered_map<int, LinkNode*>::iterator next_it = fringe_it->second->right;
    cut_links(fringe_it);
    delete fringe_it->second;
    fringe.erase(fringe_it);
    fringe_it = next_it;
}

void LinkedMapPairs::cut_links(int value) {
    
}

void LinkedMapPairs::cut_links(std::unordered_map<int, LinkNode*>::iterator it) {
    LinkNode* node = it->second;
    if (node->left != fringe.end() && node->right != fringe.end()) {
        node->left->second->right = node->right;
        node->right->second->left = node->left;
        // node->left = node->right;
    } else if (node->left != fringe.end()) {
        node->left->second->right = fringe.end();
    } else if (node->right != fringe.end()) {
        node->right->second->left = fringe.end();
    } else {
        std::cout << "this was the only node, no links to cut" << std::endl;
    }
    if (head == it) {
        head = node->right;
    }
    if (tail == it) {
        tail = node->left;
    }
}


