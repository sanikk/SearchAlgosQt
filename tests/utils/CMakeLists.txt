add_library(test_utils STATIC
    test_utils.h
    travel_fringe.cpp travel_fringe.h
#    exceptions.cpp exceptions.h
)
target_include_directories(test_utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(test_utils PRIVATE models searches)
