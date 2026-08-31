cmake_minimum_required(VERSION 3.5)

project(03.homework)

add_executable(guess_the_number
    guess_the_number.cpp
    argument.cpp
    argument.h
    check_value.cpp
    check_value.h
    high_scores.cpp
    high_scores.h
    random_value.cpp
    random_value.h
)

set_target_properties(guess_the_number PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
