add_library(models STATIC
    node.h
    retval.h
    scenario.h
    models.h
)
target_include_directories(models PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# target_link_libraries(models PRIVATE tools)
