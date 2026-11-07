cmake_minimum_required(VERSION 4.3)
project(revision)

set(CMAKE_CXX_STANDARD 20)

add_executable(revision main.cpp
        Fan.h
        Thermostat.h)
