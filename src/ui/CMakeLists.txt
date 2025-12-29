add_library(ui STATIC
    ui.cpp ui.h
    scenario_controls.cpp scenario_controls.h
    file_selection.cpp file_selection.h
    bucket_tab.cpp bucket_tab.h
    visual_search_tab.cpp visual_search_tab.h
    map_widget.cpp map_widget.h
    fullscreenDialog.cpp fullscreenDialog.h
    testbed_tab.cpp testbed_tab.h
)

target_include_directories(ui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ui PUBLIC models tools Qt6::Core Qt6::Widgets scenario_service shared_search_tools searches search_service)

