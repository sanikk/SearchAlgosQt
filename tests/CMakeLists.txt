include_directories(${CMAKE_SOURCE_DIR}/src/shared_search_tools/)

add_executable(children_test children_test.cpp)
add_executable(children_corner_test children_corner_test.cpp)
target_link_libraries(children_test PRIVATE models tools shared_search_tools gtest gtest_main)
target_link_libraries(children_corner_test PRIVATE models tools shared_search_tools gtest gtest_main)
add_test(NAME ChildrenTest COMMAND children_test)
add_test(NAME ChildrenCornerTest COMMAND children_corner_test)

