cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

message("Building with CMake version " ${CMAKE_VERSION})

project(OptimalFashion)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_subdirectory(OptimalFashionCore)
add_subdirectory(OptimalFashionManual)