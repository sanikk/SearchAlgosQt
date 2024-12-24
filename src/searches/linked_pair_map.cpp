#include "linked_pair_map.h"
#include <stdexcept>

LinkedPairMap::LinkedPairMap(const int& start_value, const int& map_size) {
    // ok this seems to have n**2 = int_MAX as max value. So we can reserve MAX_INT. or something.
    // I need a bigger map than this puny unordered_map ! To store more nodes!
    fringe.reserve(map_size * map_size);
    bool success = fringe.emplace(start_value, new LinkNode{start_value, fringe.end(), fringe.end()}).second;
    if (success == false) { // very cheap check. leave it.
        throw std::runtime_error("adding start node failed for some reason");
    }
    head = fringe.begin();
    tail = fringe.begin();
}

void LinkedPairMap::add_tail(const int& value) {
    work_it = fringe.find(value);
    if (work_it == fringe.end()) {
        work_it = fringe.emplace(value, new LinkNode(value, tail, fringe.end())).first;
        tail->second->right = work_it;
        tail = work_it;
        if (value != work_it->second->value) {
            throw std::runtime_error("there is something wrong with the container. value and LinkNode.value do not match.");
        }
    } else if (work_it != tail) {
        std::unordered_map<int, LinkNode*>::iterator& left = work_it->second->left;
        std::unordered_map<int, LinkNode*>::iterator& right = work_it->second->right;
        if (left != fringe.end() && right != fringe.end()) {
            left->second->right = right;
            right->second->left = left;
        } else if (work_it->second->right != fringe.end()) {
            right->second->left = fringe.end();
            head = right;
        } else {
            throw std::runtime_error("work_it should be tail, but it's not?");
        }
        tail->second->right = work_it;
        left = tail;
        right = fringe.end();
        tail = work_it;
    }
    if (value != work_it->second->value) {
        throw std::runtime_error("there is something wrong with the container. value and LinkNode.value do not match.");
    }
}

void LinkedPairMap::remove_current(std::unordered_map<int, LinkNode*>::iterator& fringe_it) {
    if (fringe_it == fringe.end()) {
        throw std::runtime_error("fringe_it equals fringe.end(). this should not happen");
    }
    auto* current_node = fringe_it->second;
    auto right = current_node->right;

    if (current_node->left != fringe.end() && current_node->right != fringe.end()) {
        current_node->right->second->left = current_node->left;
        current_node->left->second->right = current_node->right;
    } else if (current_node->right != fringe.end()) {
        current_node->right->second->left = fringe.end();
        head = current_node->right;
    } else if (current_node->left != fringe.end()) {
        current_node->left->second->right = fringe.end();
        tail = current_node->left;
    } else {
        head = current_node->right;
        tail = current_node->left;
    }
    fringe.erase(fringe_it);
    delete current_node;
    fringe_it = right;
}
