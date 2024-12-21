#include <gtest/gtest.h>
#include "linked_map_pairs.h"
#include "utils/travel_fringe.h"
#include <vector>

TEST(LinkedMapPairs_RemoveCurrent, RemoveFromMiddleWorks) {
    LinkedMapPairs fringe(111, 512);
    std::unordered_map<int, LinkNode *>::iterator fringe_it = fringe.fringe.begin();
}
