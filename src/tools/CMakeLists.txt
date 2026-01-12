add_library(tools STATIC
    tools.h
    conversions.cpp conversions.h
    exceptions.cpp exceptions.h
)
target_include_directories(tools PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(tools PUBLIC models Qt6::Core)
