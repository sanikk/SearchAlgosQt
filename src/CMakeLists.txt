add_library(search_service STATIC
    search_service.cpp
)

target_include_directories(search_service PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(search_service PRIVATE searches scenario_service)
