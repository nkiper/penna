cmake_minimum_required(VERSION 3.5)

project(penna)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Wpedantic)

add_subdirectory(source_dir)

option(BUILD_TESTS "Build the tests." ON)

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()