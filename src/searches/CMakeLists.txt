add_library(searches
    astar_search.cpp astar_search.h
    fringe_search.cpp fringe_search.h
    dll.cpp dll.h
    fringe_with_dll.cpp fringe_with_dll.h
)

target_include_directories(searches PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(searches PRIVATE models tools shared_search_tools)
