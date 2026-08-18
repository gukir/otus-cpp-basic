cmake_minimum_required(VERSION 4.0)
project(memory_model CXX)
set(CMAKE_CXX_STANDARD 20)

add_executable(stack stack.cpp)
add_executable(pointer pointer.cpp)

add_executable(reference reference.cpp)