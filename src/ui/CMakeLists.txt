add_library(ui STATIC
    ui.cpp ui.h
    scenario_controls.cpp scenario_controls.h
    bucket_tab.cpp bucket_tab.h
    search_tabs.cpp search_tabs.h
)

target_include_directories(ui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ui PUBLIC Qt6::Core Qt6::Widgets scenario_service)

