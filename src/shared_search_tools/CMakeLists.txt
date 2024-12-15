add_library(shared_search_tools STATIC
    shared_search_tools.h
    children.cpp children.h
    heuristics.cpp heuristics.h
    adjust.cpp adjust.h
)
target_include_directories(shared_search_tools PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(shared_search_tools PRIVATE models)
