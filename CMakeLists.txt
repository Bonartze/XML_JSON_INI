cmake_minimum_required(VERSION 3.26)
project(names)

set(CMAKE_CXX_STANDARD 17)

add_executable(names main.cpp xml.cpp json.cpp)
