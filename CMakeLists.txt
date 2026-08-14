cmake_minimum_required(VERSION 3.22)

project(03.Syntax_1)

add_executable(0_previous 0_previous.cpp)
set_target_properties(
    0_previous
    PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON
)

add_executable(1_while 1_while.cpp)
set_target_properties(
    1_while
    PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON
)

add_executable(2_while_continue 2_while_continue.cpp)
set_target_properties(
    2_while_continue
    PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON
)

add_executable(3_while_break 3_while_break.cpp)
set_target_properties(
    3_while_break
    PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON
)

add_executable(4_for 4_for.cpp)
set_target_properties(
    4_for
    PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON
)

add_executable(5_for_strcmp 5_for_strcmp.cpp)
set_target_properties(
    5_for_strcmp
    PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON
)

add_executable(6_for_complex 6_for_complex.cpp)
set_target_properties(
    6_for_complex
    PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON
)

add_executable(7_namespace 7_namespace.cpp)
set_target_properties(
    7_namespace
    PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON
)

add_executable(8_switch 8_switch.cpp)
set_target_properties(
    8_switch
    PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON
)

add_executable(9_files 9_files.cpp)
set_target_properties(
    9_files
    PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON
)

