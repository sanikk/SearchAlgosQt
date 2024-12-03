add_library(ui STATIC
    ui.cpp ui.h
    scenario_controls.cpp scenario_controls.h
)

target_include_directories(ui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ui PUBLIC Qt6::Widgets)

