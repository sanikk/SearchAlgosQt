#include "heuristics.h"
#include "children.h"
#include <gtest/gtest.h>

namespace {

TEST(difference, isApproximatelyRight) {
  // EXPECT_EQ(DIFF, -0.58578643762);
  EXPECT_LT(DIFF, -0.58578643762);
  EXPECT_GT(DIFF, -0.58578643763);
}

TEST(movementCost, oneStepStraight) {
  EXPECT_EQ(heuristics(1,1, 2, 1), 1.0);
  EXPECT_EQ(heuristics(1,1, 1, 2), 1.0);
  EXPECT_EQ(heuristics(1,1, 0, 1), 1.0);
  EXPECT_EQ(heuristics(1,1, 1, 0), 1.0);
}
TEST(movementCost, diagonalCost) {
  EXPECT_EQ(heuristics(1,1, 2, 2), DIAG);
  EXPECT_EQ(heuristics(1,1, 2, 0), DIAG);
  EXPECT_EQ(heuristics(1,1, 0, 0), DIAG);
  EXPECT_EQ(heuristics(1,1, 0, 2), DIAG);
}

TEST(movent, usesOctile) {
  // EXPECT_NE(3 * DIFF + 2,3 );
  EXPECT_EQ(heuristics(14, 18, 17, 23), 3 * DIAG + 2);
}

}// double heuristics(int nodex, int nodey, int goalx, int goaly, double diff) {
