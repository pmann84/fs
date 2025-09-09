cmake_minimum_required(VERSION 3.14)

project(
        fs
        VERSION 1.0
        DESCRIPTION "Cross platform file listing program. Based on linux ls."
        LANGUAGES CXX
)

set(CMAKE_SUPPRESS_REGENERATION true)
set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON" FORCE)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(vendor/sage)
add_subdirectory(fs)