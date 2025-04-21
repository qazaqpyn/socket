cmake_minimum_required(VERSION 3.15)
project(socket_project VERSION 1.0.0 LANGUAGES CXX)

# Specify C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Force using clang++
set(CMAKE_CXX_COMPILER "clang++")

# Enable compiler warnings
add_compile_options(-Wall -Wextra -Wpedantic)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/include)

# Create socket library
add_library(socket_lib
    src/socket.cpp
)

# Set include directories for the library
target_include_directories(socket_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include
)

# Server executable
add_executable(server
    src/server.cpp
)
target_link_libraries(server PRIVATE socket_lib)

# Client executable
add_executable(client
    src/client.cpp
)
target_link_libraries(client PRIVATE socket_lib)