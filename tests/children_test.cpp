#include "searches_common.h"
#include <gtest/gtest.h>
#include <vector>
#include <string>

namespace {

// all are simple wrappers so imma just test them all indiscriminately.
TEST(children_with_nodes, gives_8_back_on_empty) {
  std::vector<std::string> empty_map{"...", "...", "..."};
  std::vector<Node> vec;
  children(1, 1, empty_map, vec);

  EXPECT_EQ(vec.size(), 8);

  std::vector<Node> vec2{
    Node(1, 0, 1.0),
    Node(0, 0, DIAG),
    Node(0, 1, 1.0),
    Node(0, 2, DIAG),
    Node(1, 2, 1.0),
    Node(2, 2, DIAG),
    Node(2, 1, 1.0),
    Node(2, 0, DIAG)
  };

  // debug leftovers, imma leave them.
  for (int i=0; i < 8; i++) {
    EXPECT_EQ(vec[i].x, vec2[i].x);
    EXPECT_EQ(vec[i].y, vec2[i].y);
    EXPECT_EQ(vec[i].cost, vec2[i].cost);
  }
  // can do this too now it that it works:
  EXPECT_EQ(vec, vec2);
}
// TEST(children, test_edges) {
// std::tuple<int, int, std::tuple<std::tuple<int, int, double>>> scens = {
//     {0,1, {{0, 0, 1.0},{0, 2, 1.0},{1, 2, DIAG},{1, 1, 1.0},{1, 0, DIAG}}}
//   };
// }

TEST(children_with_tuple, map_edges_respected_W) {
  std::vector<std::string> le_map{"...","...","..."};
  std::vector<std::tuple<int, int, double>> node_list;
  children(0, 1, le_map, node_list); 
  EXPECT_EQ(node_list.size(), 5);
  std::vector<std::tuple<int, int, double>> vec2{
    {0, 0, 1.0},
    {0, 2, 1.0},
    {1, 2, DIAG},
    {1, 1, 1.0},
    {1, 0, DIAG}
  };
  EXPECT_EQ(node_list, vec2);
}

TEST(children_with_tuple, map_edges_respected_E) {
  std::vector<std::string> le_map{"...","...","..."};
  std::vector<std::tuple<int, int, double>> node_list;
  children(2, 1, le_map, node_list); 
  EXPECT_EQ(node_list.size(), 5);

std::vector<std::tuple<int, int, double>> vec2{
    {2, 0, 1.0},
    {1, 0, DIAG},
    {1, 1, 1.0},
    {1, 2, DIAG},
    {2, 2, 1.0},
  };

  EXPECT_EQ(node_list, vec2);
}

TEST(children_with_tuple, map_edges_respected_N) {
  std::vector<std::string> le_map{"...","...","..."};
  std::vector<std::tuple<int, int, double>> node_list;
  children(1, 0, le_map, node_list); 
  EXPECT_EQ(node_list.size(), 5);

  std::vector<std::tuple<int, int, double>> vec2{
    {0, 0, 1.0},
    {0, 1, DIAG},
    {1, 1, 1.0},
    {2, 1, DIAG},
    {2, 0, 1.0},
  };

  EXPECT_EQ(node_list, vec2);
}

TEST(children_with_tuple, map_edges_respected_S) {
  std::vector<std::string> le_map{"...","...","..."};
  std::vector<std::tuple<int, int, double>> node_list;
  children(1, 2, le_map, node_list); 
  EXPECT_EQ(node_list.size(), 5);
  std::vector<std::tuple<int, int, double>> vec2{
    {1, 1, 1.0},
    {0, 1, DIAG},
    {0, 2, 1.0},
    {2, 2, 1.0},
    {2, 1, DIAG}
  };

  EXPECT_EQ(node_list, vec2);
}


TEST(children_with_tuple, map_edges_respected_NW) {
  std::vector<std::string> le_map{"...","...","..."};
  std::vector<std::tuple<int, int, double>> node_list;
  children(0, 0, le_map, node_list); 
  EXPECT_EQ(node_list.size(), 3);
  std::vector<std::tuple<int, int, double>> vec2{
    {0, 1, 1.0},
    {1, 1, DIAG},
    {1, 0, 1.0},
  };

  EXPECT_EQ(node_list, vec2);
}


TEST(children_with_tuple, map_edges_respected_SW) {
  std::vector<std::string> le_map{"...","...","..."};
  std::vector<std::tuple<int, int, double>> node_list;
  children(0, 2, le_map, node_list); 
  EXPECT_EQ(node_list.size(), 3);
  std::vector<std::tuple<int, int, double>> vec2{
    {0, 1, 1.0},
    {1, 2, 1.0},
    {1, 1, DIAG}
  };

  EXPECT_EQ(node_list, vec2);
}


TEST(children_with_tuple, map_edges_respected_SE) {
  std::vector<std::string> le_map{"...","...","..."};
  std::vector<std::tuple<int, int, double>> node_list;
  children(2, 2, le_map, node_list); 
  EXPECT_EQ(node_list.size(), 3);
  std::vector<std::tuple<int, int, double>> vec2{
    {2, 1, 1.0},
    {1, 1, DIAG},
    {1, 2, 1.0},
  };

  EXPECT_EQ(node_list, vec2);
}


TEST(children_with_tuple, map_edges_respected_NE) {
  std::vector<std::string> le_map{"...","...","..."};
  std::vector<std::tuple<int, int, double>> node_list;
  children(2, 0, le_map, node_list); 
  EXPECT_EQ(node_list.size(), 3);
  std::vector<std::tuple<int, int, double>> vec2{
    {1, 0, 1.0},
    {1, 1, DIAG},
    {2, 1, 1.0},
  };

  EXPECT_EQ(node_list, vec2);
}

}// namespace ends
