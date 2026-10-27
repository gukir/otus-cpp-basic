cmake_minimum_required(VERSION 3.2)

project(ProjestWithGTest)

include(FetchContent)
FetchContent_Declare(
  GTest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(GTest)


# Test target
add_executable(
    test_assertions
    test/test_assertions.cpp
)
target_compile_features(test_assertions PUBLIC cxx_std_20)
target_link_libraries(test_assertions PRIVATE GTest::gtest_main)
target_include_directories(test_assertions PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(
    test_fixtures
    test/test_fixtures.cpp
)
target_compile_features(test_fixtures PUBLIC cxx_std_20)
target_link_libraries(test_fixtures PRIVATE gtest_main)
target_include_directories(test_fixtures PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(
    test_mocks
    test/test_mocks.cpp
)
target_compile_features(test_mocks PUBLIC cxx_std_20)
target_link_libraries(test_mocks PRIVATE gtest_main gmock_main)
target_include_directories(test_mocks PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)


if (MSVC)
    # @see https://github.com/google/googletest/blob/master/googletest/README.md
    # Visual Studio Dynamic vs Static Runtimes
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()
