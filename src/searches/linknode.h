#include <unordered_map>

struct LinkNode {

    std::unordered_map<int, LinkNode*>::iterator left;
    std::unordered_map<int, LinkNode*>::iterator right;
    int value;

    explicit LinkNode(int i_value, std::unordered_map<int, LinkNode*>::iterator i_left, std::unordered_map<int, LinkNode*>::iterator i_right)
        : value(i_value), left(i_left), right(i_right) {}
};
