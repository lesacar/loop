cmake_minimum_required(VERSION 3.0)
project(loop)

# Set source files
set(SOURCES src/main.c)

# Set the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)

# Add executable
add_executable(loop ${SOURCES})

