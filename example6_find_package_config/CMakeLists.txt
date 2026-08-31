cmake_minimum_required(VERSION 3.22)

project(example6 VERSION 0.0.6)

configure_file(
        config.h.in 
        ${CMAKE_CURRENT_BINARY_DIR}/config.h
)

add_executable(mainLib main.cpp)
set_target_properties(
        mainLib PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)
target_include_directories(
        mainLib 
        PRIVATE 
        ${CMAKE_CURRENT_BINARY_DIR}
)

set(CMAKE_MODULE_PATH 
        ${CMAKE_MODULE_PATH}
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

find_package(sumLib CONFIG REQUIRED)
target_link_libraries(mainLib SumLib::sumLib)