add_library(search_service STATIC
    search_service.cpp search_service.h
)

target_include_directories(search_service PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(search_service PRIVATE models tools searches scenario_service)
