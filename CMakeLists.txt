cmake_minimum_required(VERSION 3.13)
project(Procedure)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx2")

add_executable(Procedure main.cpp)