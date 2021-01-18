cmake_minimum_required(VERSION 3.15)
project(polynome)

set(CMAKE_CXX_STANDARD 14)

add_executable(polynome division.cpp polynome.cpp main.cpp rationnel.cpp)