cmake_minimum_required(VERSION 4.3)
project(esp32ServoRadar)

set(CMAKE_CXX_STANDARD 20)

add_executable(esp32ServoRadar main.cpp
        Blinker.h)
