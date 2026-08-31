cmake_minimum_required(VERSION 3.22)

project(Example1)

add_executable(helloWorld main.cpp)

set_target_properties(
        helloWorld PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

#some_function_from_3_32()