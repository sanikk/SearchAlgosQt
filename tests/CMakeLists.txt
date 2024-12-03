include_directories(${CMAKE_SOURCE_DIR}/src/searches/common)

add_executable(children_test children_test.cpp)
add_executable(children_corner_test children_corner_test.cpp)
target_link_libraries(children_test PRIVATE searches_common gtest gtest_main)
target_link_libraries(children_corner_test PRIVATE searches_common gtest gtest_main)
add_test(NAME ChildrenTest COMMAND children_test)
add_test(NAME ChildrenCornerTest COMMAND children_corner_test)

