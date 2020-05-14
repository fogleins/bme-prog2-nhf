cmake_minimum_required(VERSION 3.16)
project(filmtar)

set(CMAKE_CXX_STANDARD 98)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
add_executable(filmtar main.cpp collection.cpp collection.h movie.cpp movie.h family.cpp family.h documentary.cpp documentary.h data.cpp data.hpp)