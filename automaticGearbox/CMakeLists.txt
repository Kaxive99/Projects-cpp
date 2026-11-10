cmake_minimum_required(VERSION 4.3)
project(automaticGearbox)

set(CMAKE_CXX_STANDARD 20)

add_executable(automaticGearbox main.cpp
        gearsEcu.h)
