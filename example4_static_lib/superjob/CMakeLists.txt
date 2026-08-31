cmake_minimum_required(VERSION 3.22)

project(Library VERSION 0.0.2)

configure_file(
        config.h.in
        ${CMAKE_CURRENT_BINARY_DIR}/config.h
)

add_library(superjob STATIC superjob.cpp superjob.h)
set_target_properties(
        superjob PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)
target_include_directories(
        superjob 
        PRIVATE 
        ${CMAKE_CURRENT_BINARY_DIR}
)