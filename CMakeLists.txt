cmake_minimum_required(VERSION 3.20)
project(SearchAlgoProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

set(CMAKE_AUTOMOC ON)

add_subdirectory(src/models)
add_subdirectory(src/tools)
add_subdirectory(src/scenario_service)
add_subdirectory(src/shared_search_tools)
add_subdirectory(src/searches)
add_subdirectory(src/search_service)
add_subdirectory(src/ui)

add_executable(searchalgos src/main.cpp)
target_link_libraries(searchalgos PRIVATE models tools shared_search_tools Qt6::Core Qt6::Widgets scenario_service search_service ui)

# enable_testing()
# add_subdirectory(tests)

