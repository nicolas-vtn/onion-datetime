cmake_minimum_required(VERSION 3.20)

project(onion_datetime LANGUAGES CXX)

# ---- Library ----
add_library(onion_datetime
    onion/DateTime.cpp
)
add_library(onion::datetime ALIAS onion_datetime)

target_include_directories(onion_datetime
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(onion_datetime PUBLIC cxx_std_20)

set_target_properties(onion_datetime PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# ---- Demo ----
option(BUILD_ONION_DEMO "Build DateTime demo" ON)

if (BUILD_ONION_DEMO)
    add_subdirectory(demo)
endif()

# ---- Tests ----
option(BUILD_ONION_TESTS "Build DateTime tests" ON)

if (BUILD_ONION_TESTS)
    add_subdirectory(tests)
endif()
