#include "linked_map_pairs.h"
#include <cassert>
#include <iostream>

LinkedMapPairs::LinkedMapPairs(int start, int map_size) {
    fringe = {};
    fringe.reserve(map_size * map_size);
    add_first(start);

    // std::unordered_map<int, LinkNode*>::iterator it = fringe.begin();
    // head = it;
    tail = fringe.begin();
}

void LinkedMapPairs::add_first(int value) {
    if (fringe.begin() != fringe.end()) {
        throw std::runtime_error("LinkedMapPairs.add_first: fringe was not empty!");
    }
    fringe.emplace(value, new LinkNode(value, fringe.end(), fringe.end()));
}

void LinkedMapPairs::add_tail(int value) {
    std::unordered_map<int, LinkNode*>::iterator it = fringe.find(value);
    assert(typeid(it) == typeid(std::unordered_map<int, LinkNode*>::iterator));
    if (it != fringe.end()) {
        // assert(it!=)
        cut_links(it);
    } else {
        it = fringe.emplace(value, new LinkNode{value, tail, fringe.end()}).first;

        assert(typeid(it) == typeid(std::unordered_map<int, LinkNode*>::iterator) && "Iterator is NOT of the right type");
        assert(it != fringe.end() && "iterator should not point at end, after emplace");
    }
    if (tail == fringe.end()) {
        throw std::runtime_error("LinkedMapPairs.add_tail: tail was empty!");
    }
    tail->second->right = it;
    tail = it;
}

void LinkedMapPairs::remove_current(std::unordered_map<int, LinkNode*>::iterator& fringe_it) {
    static_assert(std::is_same_v<decltype(fringe_it), std::unordered_map<int, LinkNode*>::iterator&>, "Iterator type is incorrect");
    assert(fringe_it != fringe.end() && "fringe_it should point at valid node, now it points at fringe.end()");
    std::unordered_map<int, LinkNode*>::iterator next_it = fringe_it->second->right;
    cut_links(fringe_it);
    delete fringe_it->second;
    fringe.erase(fringe_it);
    fringe_it = next_it;
}

void LinkedMapPairs::cut_links(std::unordered_map<int, LinkNode*>::iterator it) {
    LinkNode* node = it->second;
    // static_assert(std::is_same_v<decltype(node->left), std::unordered_map<int, LinkNode*>::iterator&>, "Iterator type is incorrect");
    if (node->left != fringe.end() && node->right != fringe.end()) {
        // static_assert(std::is_same_v<decltype(node->left), std::unordered_map<int, LinkNode*>::iterator&>, "Iterator type is incorrect");

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
    // if (head == it) {
    //     head = node->right;
    // }
    if (tail == it) {
        tail = node->left;
    }
}

std::unordered_map<int, LinkNode*>::iterator LinkedMapPairs::begin() { return fringe.begin(); }

std::unordered_map<int, LinkNode*>::iterator LinkedMapPairs::end() { return fringe.end(); }
