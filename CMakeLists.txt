cmake_minimum_required(VERSION 3.5)

project(03.cpp)

add_executable(rvo rvo.cpp)
add_executable(values values.cpp)
add_executable(move move.cpp)
add_executable(move_additional move_additional.cpp)


set_target_properties(rvo values move PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )


set_target_properties(move_additional PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )
