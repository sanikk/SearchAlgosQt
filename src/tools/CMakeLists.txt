add_library(tools STATIC
    tools.cpp tools.h
)
target_include_directories(tools PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(tools PRIVATE models)
