cmake_minimum_required(VERSION 3.21)
project(ConwayGameofLife)

set(CMAKE_CXX_STANDARD 14)

add_executable(ConwayGameofLife prevCode.cpp gol_skeleton_sfml.cpp gol_skeleton_text.cpp nextgen.cpp)
