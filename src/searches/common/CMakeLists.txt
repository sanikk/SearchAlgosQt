add_library(searches_common STATIC
    children.cpp
    heuristics.cpp
    adjust.cpp
)
target_include_directories(searches_common PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(searches_common PRIVATE models tools)
