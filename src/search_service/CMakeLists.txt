add_library(search_service STATIC
#    search_thread.h
#    astar_thread.cpp astar_thread.h
    worker.cpp worker.h
    search_service.cpp search_service.h
)

target_include_directories(search_service
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}
# from my experiments limiting the visibilty of searches to search_service.
# this made sure the contents of the directory are still accessible to search_service
# while the searches includes are marked PRIVATE. Saving this here for future reference.
#    PRIVATE
#        ${CMAKE_CURRENT_SOURCE_DIR}/../searches
)
target_link_libraries(search_service PRIVATE tools searches search_tools
                                     PUBLIC models Qt6::Core scenario_service)
