#include <gtest/gtest.h>
#include "linked_pair_map.h"

TEST(LinkedPairMap, ConstructorWorks) {
    auto fringe = LinkedPairMap(111, 512);
    ASSERT_EQ(fringe.head->first, 111);
    ASSERT_EQ(fringe.tail->first, 111);
    ASSERT_EQ(fringe.begin()->first, 111);
}

TEST(LinkedPairMap, AddTailNewValueWorks) {
    auto fringe = LinkedPairMap(111, 512);
    fringe.add_tail(222);
    ASSERT_EQ(fringe.head->first, 111);
    ASSERT_EQ(fringe.tail->first, 222);
    ASSERT_EQ(fringe.fringe.size(), 2);
    fringe.add_tail(333);
    ASSERT_EQ(fringe.head->first, 111);
    ASSERT_EQ(fringe.tail->first, 333);
    ASSERT_EQ(fringe.fringe.size(), 3);
}

TEST(LinkedPairMap, AddTailSameValueWorks) {
    auto fringe = LinkedPairMap(111, 512);
    // readd only value
    fringe.add_tail(111);
    ASSERT_EQ(fringe.head->first, 111);
    ASSERT_EQ(fringe.tail->first, 111);
    ASSERT_EQ(fringe.fringe.size(), 1);

    // this is adding new value, not same
    fringe.add_tail(222);
    ASSERT_EQ(fringe.head->first, 111);
    ASSERT_EQ(fringe.tail->first, 222);
    ASSERT_EQ(fringe.fringe.size(), 2);
    // readd head
    fringe.add_tail(111);
    ASSERT_EQ(fringe.head->first, 222);
    ASSERT_EQ(fringe.tail->first, 111);
    ASSERT_EQ(fringe.fringe.size(), 2);
    // readd tail when it's not head too
    fringe.add_tail(111);
    ASSERT_EQ(fringe.head->first, 222);
    ASSERT_EQ(fringe.tail->first, 111);
    ASSERT_EQ(fringe.fringe.size(), 2);
    // readd current head
    fringe.add_tail(222);
    ASSERT_EQ(fringe.head->first, 111);
    ASSERT_EQ(fringe.tail->first, 222);
    ASSERT_EQ(fringe.fringe.size(), 2);
    // add a new value
    fringe.add_tail(333);
    ASSERT_EQ(fringe.head->first, 111);
    ASSERT_EQ(fringe.tail->first, 333);
    ASSERT_EQ(fringe.fringe.size(), 3);
}
