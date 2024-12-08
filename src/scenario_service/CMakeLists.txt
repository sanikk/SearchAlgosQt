add_library(scenario_service STATIC
    scenario_service.cpp scenario_service.h
    filereader.cpp filereader.h
)
target_include_directories(scenario_service PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(scenario_service PRIVATE models tools)
