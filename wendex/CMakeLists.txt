cmake_minimum_required(VERSION 3.17)
project(wendex)

set(CMAKE_CXX_STANDARD 20)

add_executable(wendex main.cpp Persons.h worldData.h System.h)