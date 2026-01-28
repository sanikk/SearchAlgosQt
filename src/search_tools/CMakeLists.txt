add_library(search_tools STATIC
    search_tools.h
    children.cpp children.h
    heuristics.cpp heuristics.h
    adjust.cpp adjust.h
)
target_include_directories(search_tools PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(search_tools PUBLIC models 
                                   PRIVATE tools) 
