cmake_minimum_required(VERSION 3.5)

project(06.homework)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

add_executable(containers containers.cpp
    my_vector.h
    my_container.h
    my_slist.h
    my_dlist.h)
set_target_properties(containers PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

# 1. Подключаем модуль FetchContent
include(FetchContent)

# 2. Объявляем зависимость от GoogleTest (скачиваем с GitHub)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.0  # Укажите актуальную версию или нужный тег/коммит
)

# Для Windows (предотвращает перезапись настроек среды выполнения CRT)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# 3. Делаем цели GoogleTest доступными в проекте
FetchContent_MakeAvailable(googletest)

# Включаем поддержку тестирования через CTest
enable_testing()

# 4. Создаем исполняемый файл для ваших тестов
add_executable(unit_tests
  tests/test_vector.cpp
  tests/fixture_vector.hpp
  tests/test_list.cpp
  tests/fixture_list.hpp
)

# 5. Подключаем библиотеки GTest и GTest main
target_link_libraries(unit_tests
  GTest::gtest_main
)
