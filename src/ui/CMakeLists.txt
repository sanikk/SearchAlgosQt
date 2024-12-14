add_library(ui STATIC
    ui.cpp ui.h
    scenario_controls.cpp scenario_controls.h
    file_selection.cpp file_selection.h
    bucket_tab.cpp bucket_tab.h
    search_tabs.cpp search_tabs.h
    map_scene.cpp map_scene.h
    fullscreenDialog.cpp fullscreenDialog.h
    # graphics_image_item.cpp graphics_image_item.h
)

target_include_directories(ui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ui PUBLIC models tools Qt6::Core Qt6::Widgets scenario_service search_service)

