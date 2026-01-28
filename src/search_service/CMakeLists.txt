add_library(search_service STATIC
    worker.cpp worker.h
    search_service.cpp search_service.h
)

target_include_directories(search_service PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(search_service PRIVATE tools searches search_tools
                                     PUBLIC models Qt6::Core scenario_service)
