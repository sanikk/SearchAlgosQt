
#include "searches_common.h"
#include <gtest/gtest.h>
#include <vector>
#include <string>

namespace {

  std::vector<std::tuple<int, int, double>> vec2{
      {1, 0, 1.0},
      {0, 0, DIAG},
      {0, 1, 1.0},
      {0, 2, DIAG},
      {1, 2, 1.0},
      {2, 2, DIAG},
      {2, 1, 1.0},
      {2, 0, DIAG}
      };
  }

struct ChildrenTestCase {
  std::vector<std::string> map_input;
  std::string bools;
  std::vector<std::tuple<int, int, double>> results;

  ChildrenTestCase(std::vector<std::string> i_map, std::string i_bools) : map_input(i_map), bools(i_bools) {};
  ChildrenTestCase() {};
};


std::vector<std::tuple<int, int, double>> vec_for(std::string bools) {
  std::vector<std::tuple<int, int, double>> returnable;
  for (int i=0; i < bools.size(); i++) {
    if (bools[i] == '1') {
      returnable.push_back(vec2[i]);
    }
  }
  return returnable;
}


// initializer_list constructor tests
std::initializer_list<std::tuple<int, int, double>> full_list = {
      {1, 0, 1.0},
      {0, 0, DIAG},
      {0, 1, 1.0},
      {0, 2, DIAG},
      {1, 2, 1.0},
      {2, 2, DIAG},
      {2, 1, 1.0},
      {2, 0, DIAG}
  };
TEST(children_with_nodes, blocker_corner) {
  std::vector<ChildrenTestCase> testcases = {
    { {"#..", "...", "..."}, "10111111" },
    { {"..#", "...", "..."}, "11111110" },
    { {"...", "...", "#.."}, "11101111" },
    { {"...", "...", "..#"}, "11111011" }
  };
  std::vector<std::tuple<int, int, double>> node_list;
  for (ChildrenTestCase tc : testcases) {
    node_list.clear();
    children(1,1, tc.map_input, node_list);
    EXPECT_EQ(node_list, vec_for(tc.bools));
  }
}

TEST(children_with_nodes, blocked_straight) {
  std::vector<ChildrenTestCase> testcases = {
    { {".#.", "...", "..."}, "00111110" },
    { {"...", "#..", "..."}, "10001111" },
    { {"...", "..#", "..."}, "11111000" },
    { {"...", "...", ".#."}, "11100011" }
  };

  std::vector<std::tuple<int, int, double>> node_list;
  for (ChildrenTestCase tc : testcases) {
    node_list.clear();
    children(1,1, tc.map_input, node_list);
    EXPECT_EQ(node_list, vec_for(tc.bools));
  }
}

TEST(children_with_nodes, alley_between_blocked_corners) {
  std::vector<ChildrenTestCase> testcases = {
    { { "#.#", "...", "..."}, "10111110" },
    { { "#..", "...", "#.."}, "10101111" },
    { { "...", "...", "#.#"}, "11101011" },
    { { "..#", "...", "..#"}, "11111010" }
  };
  std::vector<std::tuple<int, int, double>> node_list;
  for (ChildrenTestCase tc : testcases) {
    node_list.clear();
    children(1,1, tc.map_input, node_list);
    EXPECT_EQ(node_list, vec_for(tc.bools));
  }
}

TEST(children_with_nodes, narrow_alley_NS) {
  std::vector<ChildrenTestCase> testcases = {
    { { "#.#","#.#","#.#"}, "10001000" },
    { { "..#","#.#","#.#"}, "10001000" },
    { { "#..","#.#","#.#"}, "10001000" },
    { { "#.#","..#","#.#"}, "10101000" },
    { { "#.#","#..","#.#"}, "10001010" },
    { { "#.#","#.#","..#"}, "10001000" },
    { { "#.#","#.#","#.."}, "10001000" },
  };
  std::vector<std::tuple<int, int, double>> node_list;
  for (ChildrenTestCase tc : testcases) {
    node_list.clear();
    children(1,1, tc.map_input, node_list);
    EXPECT_EQ(node_list, vec_for(tc.bools));
  }
}

TEST(children_with_nodes, narrow_alley_EW) {

  std::vector<ChildrenTestCase> testcases = {

    { { "###","...","###"}, "00100010" },
    { { ".##","...","###"}, "00100010" },
    { { "#.#","...","###"}, "10100010" },
    { { "##.","...","###"}, "00100010" },
    { { "###","...",".##"}, "00100010" },
    { { "###","...","#.#"}, "00101010" },
    { { "###","...","##."}, "00100010" },
  };
  std::vector<std::tuple<int, int, double>> node_list;
  for (ChildrenTestCase tc : testcases) {
    node_list.clear();
    children(1,1, tc.map_input, node_list);
    EXPECT_EQ(node_list, vec_for(tc.bools));
  }
}

/*
TEST(children_with_nodes, narrow_alley_EW2) {
  std::vector<ChildrenTestCase> testcases = {
    { { "#.#","#.#","#.#"}, "11111111" },

    
    { { "..#","...","..#"}, "11111111" },
    { { "###","...","###"}, "11111111" },
    { { "...","...","..."}, "11111111" },
    { { "...","...","..."}, "11111111" },
    { { "...","...","..."}, "11111111" }
  };

  std::vector<std::tuple<int, int, double>> node_list;
  for (ChildrenTestCase tc : testcases) {
    node_list.clear();
    children(1,1, tc.map_input, node_list);
    EXPECT_EQ(node_list, vec_for(tc.bools));
  }
}

TEST(children_with_nodes, narrow_alley_NS1) {
  std::vector<ChildrenTestCase> testcases = {
    { { "#.#","#.#","#.#"}, "11111111" },

    
    { { "..#","...","..#"}, "11111111" },
    { { "###","...","###"}, "11111111" },
    { { "...","...","..."}, "11111111" },
    { { "...","...","..."}, "11111111" },
    { { "...","...","..."}, "11111111" }
  };

  std::vector<std::tuple<int, int, double>> node_list;
  for (ChildrenTestCase tc : testcases) {
    node_list.clear();
    children(1,1, tc.map_input, node_list);
    EXPECT_EQ(node_list, vec_for(tc.bools));
  }
}
*/

TEST(children_with_nodes, three_blocked_corners) {
  std::vector<ChildrenTestCase> testcases = {
    { { "#.#","...","..#"}, "10111010" },
    { { "#..","...","#.#"}, "10101011" },
    { { "#.#","...","#.."}, "10101110" },
    { { "..#","...","#.#"}, "11101010" }
  };
  std::vector<std::tuple<int, int, double>> node_list;
  for (ChildrenTestCase tc : testcases) {
    node_list.clear();
    children(1,1, tc.map_input, node_list);
    EXPECT_EQ(node_list, vec_for(tc.bools));
  }
}
//namespace
