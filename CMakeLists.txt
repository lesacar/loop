cmake_minimum_required(VERSION 3.0)
project(loop)

# Set source files
set(SOURCES src/main.c)

if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # additional warnings
    add_compile_options(-Wall -Wextra -Wpedantic)
	add_compile_options(-O3 -flto -static)
endif()

# Set the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)

# Add executable
add_executable(loop ${SOURCES})

