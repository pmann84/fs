cmake_minimum_required(VERSION 3.14)

project(
        fs
        VERSION 1.0
        DESCRIPTION "Cross platform file listing program. Based on linux ls."
        LANGUAGES CXX
)

# Disable the ZERO_CHECK project generation
set(CMAKE_SUPPRESS_REGENERATION true)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(vendor/sage)
add_subdirectory(fs)