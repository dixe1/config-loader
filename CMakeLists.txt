cmake_minimum_required(VERSION 3.20)
project(ConfigLoader)

set(CMAKE_CXX_STANDARD 23)

add_library(ConfigLoader STATIC ConfigLoader.cpp)
