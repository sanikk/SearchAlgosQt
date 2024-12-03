set(TARGET_NAME scenario_service)

add_library(${TARGET_NAME}
    scenario_service.cpp
    filereader.cpp
)

target_include_directories(${TARGET_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR} # Includes scenario_service.h, filereader.h, and scenario.h
)

target_compile_features(${TARGET_NAME} PRIVATE cxx_std_17)
