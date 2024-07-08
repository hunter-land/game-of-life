cmake_minimum_required(VERSION 3.16.2)
project(gol)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include") # Private/internal include dir
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src") #source dir
#include(GNUInstallDirs) #GNUInstallDirs (a default module) is required for this CMake

# Defaults
set(CMAKE_CXX_FLAGS_RELEASE "-Os ${CMAKE_CXX_FLAGS_RELEASE}")

# Files
set(SOURCE_FILES "${SOURCE_DIR}/main.cpp" "${SOURCE_DIR}/cellBoard.cpp")
set(HEADER_FILES "${INCLUDE_DIR}/cellBoard.hpp")

# Application
add_executable(gol ${SOURCE_FILES})
target_include_directories(gol PRIVATE ${INCLUDE_DIR})

# Define install options, in case you want to install this for some reason
install(TARGETS gol)
