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

TEST(LinkedPairMap, ReAddOnlyValueWorks) {
    auto fringe = LinkedPairMap(111, 512);
    // readd only value
    fringe.add_tail(111);
    ASSERT_EQ(fringe.head->first, 111);
    ASSERT_EQ(fringe.tail->first, 111);
    ASSERT_EQ(fringe.fringe.size(), 1);
    fringe.add_tail(111);
    ASSERT_EQ(fringe.head->first, 111);
    ASSERT_EQ(fringe.tail->first, 111);
    ASSERT_EQ(fringe.fringe.size(), 1);
}
TEST(LinkedPairMap, ReAddHeadValueWorks) {
    auto fringe = LinkedPairMap(111, 512);
    fringe.add_tail(222);
    fringe.add_tail(111);
    ASSERT_EQ(fringe.head->first, 222);
    ASSERT_EQ(fringe.tail->first, 111);
    ASSERT_EQ(fringe.fringe.size(), 2);
    fringe.add_tail(222);
    ASSERT_EQ(fringe.head->first, 111);
    ASSERT_EQ(fringe.tail->first, 222);
    ASSERT_EQ(fringe.fringe.size(), 2);
}
TEST(LinkedPairMap, ReAddMiddleValuesWorks) {
    auto fringe = LinkedPairMap(111, 512);
    fringe.add_tail(222);
    fringe.add_tail(333);
    fringe.add_tail(444);
    ASSERT_EQ(fringe.head->first, 111);
    ASSERT_EQ(fringe.tail->first, 444);
    ASSERT_EQ(fringe.fringe.size(), 4);
    // readd tail when it's not head too
    fringe.add_tail(222);
    ASSERT_EQ(fringe.head->first, 111);
    ASSERT_EQ(fringe.tail->first, 222);
    ASSERT_EQ(fringe.fringe.size(), 4);
    // readd current head
    fringe.add_tail(333);
    ASSERT_EQ(fringe.head->first, 111);
    ASSERT_EQ(fringe.tail->first, 333);
    ASSERT_EQ(fringe.fringe.size(), 4);
    // add a new value
    fringe.add_tail(444);
    ASSERT_EQ(fringe.head->first, 111);
    ASSERT_EQ(fringe.tail->first, 444);
    ASSERT_EQ(fringe.fringe.size(), 4);
}

TEST(LinkedPairMap, ReAddTailValuesWorks) {
    auto fringe = LinkedPairMap(111, 512);
    fringe.add_tail(222);
    ASSERT_EQ(fringe.tail->first, 222);
    ASSERT_EQ(fringe.fringe.size(), 2);
    fringe.add_tail(222);
    ASSERT_EQ(fringe.tail->first, 222);
    ASSERT_EQ(fringe.fringe.size(), 2);
    fringe.add_tail(333);
    ASSERT_EQ(fringe.tail->first, 333);
    ASSERT_EQ(fringe.fringe.size(), 3);
    fringe.add_tail(333);
    ASSERT_EQ(fringe.tail->first, 333);
    ASSERT_EQ(fringe.fringe.size(), 3);
    fringe.add_tail(444);
    fringe.add_tail(555);
    ASSERT_EQ(fringe.head->first, 111);
    ASSERT_EQ(fringe.tail->first, 555);
    ASSERT_EQ(fringe.fringe.size(), 5);
    fringe.add_tail(555);
    ASSERT_EQ(fringe.head->first, 111);
    ASSERT_EQ(fringe.tail->first, 555);
    ASSERT_EQ(fringe.fringe.size(), 5);
}

// TEST(LinkedPairMap,
