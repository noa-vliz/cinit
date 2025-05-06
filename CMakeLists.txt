cmake_minimum_required(VERSION 3.13)
project(cinit C)

set(CMAKE_C_STANDARD 99)



include_directories(include)

file(GLOB_RECURSE SRC_FILES src/*.c)

add_executable(initc ${SRC_FILES})
