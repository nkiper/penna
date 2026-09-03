cmake_minimum_required(VERSION 3.5)

project(penna)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(penna main.cpp genome.cpp animal.cpp)

set(RESULTS_DIR ${CMAKE_CURRENT_BINARY_DIR}/results)