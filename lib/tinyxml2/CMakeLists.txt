cmake_minimum_required(VERSION 3.15)
project(tinyxml2 VERSION 9.0.0)

add_library(tinyxml2 tinyxml2.cpp tinyxml2.h)
add_library(tinyxml2::tinyxml2 ALIAS tinyxml2)

target_include_directories(tinyxml2 PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")