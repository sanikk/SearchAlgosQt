add_library(searches STATIC
    searches.h
    astar_search.cpp astar_search.h
    astar_with_callbacks.cpp astar_with_callbacks.h
    fringe_search.cpp fringe_search.h
    dll.cpp dll.h
    fringe_with_dll.cpp fringe_with_dll.h
)
# from my experiments limiting the visibility of searches to search_service.
# see also the src/search_service/CMakeLists.txt on how to make this work.
# target_include_directories(searches PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(searches PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(searches PRIVATE models tools shared_search_tools)
