#include <gtest/gtest.h>
#include "linked_map_pairs.h"
#include "utils/travel_fringe.h"
#include <vector>

TEST(LinkedMapPairs_Iterator, ConstructorSetsThingsRight) {
    LinkedMapPairs fringe(111, 512);

    std::unordered_map<int, LinkNode*>::iterator fringe_it = fringe.begin();
    ASSERT_EQ(fringe.head, fringe.begin());
    ASSERT_EQ(fringe.tail, fringe.begin());
    ASSERT_NE(fringe.head, fringe.tail);
}

TEST(LinkedMapPairs_Iterator, SettingInitialFringeItWorks) {
    LinkedMapPairs fringe(111, 512);
    std::unordered_map<int, LinkNode*>::iterator fringe_it = fringe.begin();
}

TEST(LinkedMapPairs_Iterator, SetupWorks) {
    LinkedMapPairs fringe(111, 512);
    std::unordered_map<int, LinkNode*>::iterator fringe_it = fringe.begin();
}
