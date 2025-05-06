# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(cinit C)
set(CMAKE_C_STANDARD 99)

include(CheckSymbolExists)
check_symbol_exists(__MUSL__ "features.h" USING_MUSL)

if(NOT USING_MUSL)
  try_compile(USING_MUSL
    ${CMAKE_BINARY_DIR}/musl_check
    ${CMAKE_SOURCE_DIR}/cmake/check_musl.c
  )
endif()

if(USING_MUSL)
  message(STATUS "musl libc detected - enabling static linking")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
  set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
  set(BUILD_SHARED_LIBS OFF)
else()
  message(STATUS "glibc detected - using dynamic linking")
endif()

if(APPLE)
  set(CMAKE_OSX_ARCHITECTURES "x86_64" CACHE STRING "Build architectures for macOS" FORCE)
endif()

include_directories(include)

file(GLOB_RECURSE SRC_FILES src/*.c)

add_executable(initc ${SRC_FILES})
