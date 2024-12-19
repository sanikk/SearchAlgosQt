#include "linked_map_pairs.h"
#include <gtest/gtest.h>

std::vector<int> travel_fringe(LinkedMapPairs fringe) {
    std::vector<int> returnable;
    auto current = fringe.head;
    returnable.push_back(current->first);
    while (current != fringe.tail) {
        current = current->second->right;
        returnable.push_back(current->first);
    }
    return returnable;
}

TEST(LinkedMapPairs_AddTail, AddNewValueWorks) { 
    LinkedMapPairs fringe = LinkedMapPairs(111);
    fringe.add_tail(222);
    EXPECT_EQ(fringe.head->first, 111);
    EXPECT_EQ(fringe.tail->first, 222);
    EXPECT_EQ(travel_fringe(fringe), std::vector<int>({111, 222}));

    fringe.add_tail(333);
    EXPECT_EQ(fringe.head->first, 111);
    EXPECT_EQ(fringe.tail->first, 333);
    EXPECT_EQ(travel_fringe(fringe), std::vector<int>({111, 222, 333}));

    fringe.add_tail(444);
    EXPECT_EQ(fringe.head->first, 111);
    EXPECT_EQ(fringe.tail->first, 444);
    EXPECT_EQ(travel_fringe(fringe), std::vector<int>({111, 222, 333, 444}));
}

TEST(LinkedMapPairs_AddTail, ReAddOldValueInMiddleWorks) { 
    LinkedMapPairs fringe = LinkedMapPairs(111);
    fringe.add_tail(222);
    fringe.add_tail(333);
    EXPECT_EQ(travel_fringe(fringe), std::vector<int>({111, 222, 333}));
    EXPECT_EQ(fringe.head->first, 111);
    EXPECT_EQ(fringe.tail->first, 444);
    // Test Setup is correct at this point
    
    fringe.add_tail(222);
    EXPECT_EQ(travel_fringe(fringe), std::vector<int>({111, 333, 222}));
    EXPECT_EQ(fringe.tail, 222);

    fringe.add_tail(333);
    EXPECT_EQ(travel_fringe(fringe), std::vector<int>({111, 222, 333}));
    EXPECT_EQ(fringe.tail, 333);

}

TEST(LinkedMapPairs_AddTail, ReAddHeadWorks) {
    LinkedMapPairs fringe = LinkedMapPairs(111);
    fringe.add_tail(222);
    fringe.add_tail(333);
    fringe.add_tail(444);
    EXPECT_EQ(travel_fringe(fringe), std::vector<int>({111, 222, 333, 444}));
    EXPECT_EQ(fringe.head->first, 111);
    EXPECT_EQ(fringe.tail->first, 444);
    // Test Setup is correct at this point

    fringe.add_tail(111);
    EXPECT_EQ(travel_fringe(fringe), std::vector<int>({222, 333, 444, 111}));
    EXPECT_EQ(fringe.head->first, 222);

    fringe.add_tail(222);
    EXPECT_EQ(travel_fringe(fringe), std::vector<int>({333, 444, 111, 222}));
    EXPECT_EQ(fringe.head->first, 333);
}

TEST(LinkedMapPairs_AddTail, ReAddTailWorks) {
    LinkedMapPairs fringe = LinkedMapPairs(111);
    fringe.add_tail(222);
    fringe.add_tail(333);
    fringe.add_tail(444);
    EXPECT_EQ(travel_fringe(fringe), std::vector<int>({111, 222, 333, 444}));
    EXPECT_EQ(fringe.head->first, 111);
    EXPECT_EQ(fringe.tail->first, 444);
    // Test Setup is correct at this point

    fringe.add_tail(444);
    EXPECT_EQ(travel_fringe(fringe), std::vector<int>({111, 222, 333, 444}));
    EXPECT_EQ(fringe.head->first, 111);
    EXPECT_EQ(fringe.tail->first, 444);

    fringe.add_tail(444);
    EXPECT_EQ(travel_fringe(fringe), std::vector<int>({111, 222, 333, 444}));
    EXPECT_EQ(fringe.head->first, 111);
    EXPECT_EQ(fringe.tail->first, 444);
}

// TEST(LinkedMapPairs_AddTail, ReAdd
