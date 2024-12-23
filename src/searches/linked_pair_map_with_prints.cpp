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
    } else if (work_it != tail) {
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

            std::cout << "tail has value: " << tail->first << std::endl;
            std::cout << "tail left points at node with value: " << tail->second->left->first << std::endl;
            std::cout << "that node has right pointing at node with value: " << tail->second->left->second->right->first << std::endl;
            std::cout << "tail right points at fringe.end(): " << (tail->second->right == fringe.end()) << std::endl;
        } else {
            throw std::runtime_error("work_it should be tail, but it's not?");
        }
        tail->second->right = work_it;
        left = tail;
        right = fringe.end();
        tail = work_it;
    }
    std::cout << std::endl << std::endl;
}

void LinkedPairMap::remove_current(std::unordered_map<int, LinkNode*>::iterator& fringe_it) {
    if (fringe_it == fringe.end()) {
        throw std::runtime_error("fringe_it equals fringe.end(). this should not happen");
    }
    auto* current_node = fringe_it->second;
    auto right = current_node->right;

    // std::unordered_map<int, LinkNode*>::iterator& left = fringe_it->second->left;
    // std::unordered_map<int, LinkNode*>::iterator& right = fringe_it->second->right;
    if (current_node->left != fringe.end() && current_node->right != fringe.end()) {
        std::cout << "fringe_it was in the middle! removing that." << std::endl;
        current_node->right->second->left = current_node->left;
        current_node->left->second->right = current_node->right;
    } else if (current_node->right != fringe.end()) {
        std::cout << "fringe_it was head! removing that." << std::endl;
        current_node->right->second->left = fringe.end();
        head = current_node->right;
    } else if (current_node->left != fringe.end()) {
        std::cout << "fringe_it was tail! removing that." << std::endl;
        current_node->left->second->right = fringe.end();
        tail = current_node->left;
        std::cout << "tail value is now: " << tail->first << std::endl;
        std::cout << "tail right equals fringe.end(): " << (tail->second->right == fringe.end()) << std::endl;
    } else {
        if (fringe.size() != 1) {
            throw std::runtime_error("remove current: node was already loose?");
        }
        head = current_node->right;
        tail = current_node->left;
    }
    fringe.erase(fringe_it);
    std::cout << "before delete." << std::endl;
    delete current_node;
    std::cout << "after delete." << std::endl;
    fringe_it = right;
    std::cout << "after resetting fringe_it." << std::endl;
}

int main(int argc, char* argv[]) {
    auto fringe = LinkedPairMap(111, 512);
    // std::unordered_map<int, LinkNode*>::iterator fringe_it = fringe.begin();
    // fringe.add_tail(222);
    // fringe.add_tail(222);
    // fringe.add_tail(333);
    // fringe.add_tail(222);
    // fringe.add_tail(111);
    // for (int i = 2; i < 6; i++) {
    //     fringe.add_tail(i * 111);
    // }
    std::unordered_map<int, LinkNode*>::iterator fringe_it = fringe.fringe.find(111);
    fringe.remove_current(fringe_it);
    if (fringe_it != fringe.end()) {
        std::cout << "after removal fringe_it.value: " << fringe_it->first << std::endl;
    } else {
        std::cout << "fringe it equal to fringe.end(): " << (fringe_it == fringe.end()) << std::endl;
    }
    // std::cout << "fringe head.value: " << fringe.head->first << ", tail.value: " << fringe.tail->first << ", size: " << fringe.fringe.size() << std::endl;
    // fringe.remove_current(fringe.fringe.find(111));
    std::cout << "fringe head equals fringe.end(): " << (fringe.head == fringe.end()) << std::endl;
    std::cout << "fringe.tail equals fringe.end(): " << (fringe.tail == fringe.end()) << std::endl;
    std::cout << "fringe size: " << fringe.fringe.size() << std::endl;
    return 0;
}
