#include "linked_pair_map.h"
#include <iostream>
#include <ostream>
#include <stdexcept>

LinkedPairMap::LinkedPairMap(const int& start_value, const int& map_size) {
    fringe.reserve(map_size * map_size);
    if (map_size > 2024) {
        throw std::invalid_argument("map_size was too big");
    }
    bool success = fringe.emplace(start_value, new LinkNode{start_value, fringe.end(), fringe.end()}).second;
    if (success == false) {
        throw std::runtime_error("adding start node failed for some reason");
    }
    head = fringe.begin();
    tail = fringe.begin();
}

void LinkedPairMap::add_tail(const int& value) {
    work_it = fringe.find(value);
    if (work_it == fringe.end()) {
        std::cout << "making new node with value " << value << std::endl;
        auto [work_it, success] = fringe.emplace(value, new LinkNode(value, tail, fringe.end()));
        if (success == false) {
            throw std::runtime_error("adding node failed for some reason");
        }
        tail->second->right = work_it;
        tail = work_it;
        std::cout << "tail is now iterator with value: " << tail->first << std::endl;
        std::cout << "iterator to the left of tail has value: " << tail->second->left->first << std::endl;
        std::cout << "and that iterators right points at node with value: " << tail->second->left->second->right->first << std::endl;
    } else {
        std::cout << "trying to replace old node with value " << value << std::endl;
        std::unordered_map<int, LinkNode*>::iterator& left = work_it->second->left;
        std::unordered_map<int, LinkNode*>::iterator& right = work_it->second->right;
        if (left != fringe.end() && right != fringe.end()) {
            std::cout << "both left and right exist" << std::endl;
            left->second->right = right;
            right->second->left = left;
            std::cout << "left " << work_it->second->left->first
                      << " has right link pointing to node with value: " << work_it->second->left->second->right->first << std::endl;
            std::cout << "right " << work_it->second->right->first
                      << " has left link pointing to node with value: " << work_it->second->right->second->left->first << std::endl;

            tail->second->right = work_it;
            left = tail;
            right = fringe.end();
            tail = work_it;
            std::cout << "tail has value: " << tail->first << std::endl;
            std::cout << "tail left points at node with value: " << tail->second->left->first << std::endl;
            std::cout << "that node has right pointing at node with value: " << tail->second->left->second->right->first << std::endl;
            std::cout << "tail right points at fringe.end(): " << (tail->second->right == fringe.end()) << std::endl;
        } else if (work_it->second->right != fringe.end()) {
            std::cout << "only right exists so this is head. moving to tail." << std::endl;
            right->second->left = fringe.end();
            head = right;
            std::cout << "new head left points now at fringe.end(): " << bool(head->second->left == fringe.end()) << std::endl;
            std::cout << "new head has value: " << head->first << std::endl;

            tail->second->right = work_it;
            left = tail;
            right = fringe.end();
            tail = work_it;

            std::cout << "tail has value: " << tail->first << std::endl;
            std::cout << "tail left points at node with value: " << tail->second->left->first << std::endl;
            std::cout << "that node has right pointing at node with value: " << tail->second->left->second->right->first << std::endl;
            std::cout << "tail right points at fringe.end(): " << (tail->second->right == fringe.end()) << std::endl;
        } else if (work_it->second->left != fringe.end()) {
            std::cout << "only left exists so this is tail. no ops needed." << std::endl;
            if (tail != work_it) {
                throw std::runtime_error("tail was not set right!");
            }
        } else {
            std::cout << "neither exists" << std::endl;
            throw std::runtime_error("add_tail: trying to readd the only node");
        }
    }
    std::cout << "fringe size: " << fringe.size() << std::endl << std::endl;
}

void LinkedPairMap::remove_current(std::unordered_map<int, LinkNode*>::iterator& fringe_it) {}
int main(int argc, char* argv[]) {
    auto fringe = LinkedPairMap(111, 512);
    std::unordered_map<int, LinkNode*>::iterator fringe_it = fringe.begin();
    fringe.add_tail(222);
    fringe.add_tail(222);
    fringe.add_tail(333);
    fringe.add_tail(222);
    fringe.add_tail(111);
    return 0;
}
