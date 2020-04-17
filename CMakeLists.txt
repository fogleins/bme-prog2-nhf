cmake_minimum_required(VERSION 3.16)
project(filmtar)

set(CMAKE_CXX_STANDARD 98)

add_executable(filmtar main.cpp collection.cpp collection.h movie.cpp movie.h)