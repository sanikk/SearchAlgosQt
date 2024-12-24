add_library(searches STATIC
    searches.h
    astar_search.cpp astar_search.h
    fringe_search.cpp fringe_search.h
    fringe_dll_version.cpp fringe_dll_version.h
    # linked_map_pairs.cpp linked_map_pairs.h
    # fringe_with_linked_map_pairs.cpp fringe_with_linked_map_pairs.h
    linked_pair_map.cpp linked_pair_map.h
    fringe_with_linked_pair_map.cpp fringe_with_linked_pair_map.h
)
# from my experiments limiting the visibility of searches to search_service.
# see also the src/search_service/CMakeLists.txt on how to make this work.
# target_include_directories(searches PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(searches PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(searches PRIVATE models tools shared_search_tools)
