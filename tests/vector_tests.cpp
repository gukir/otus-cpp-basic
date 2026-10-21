#include <gtest/gtest.h>
#include "fixture_vector.hpp"

// Перед запуском тестов с использованием фикстур
// проверим функциональность конструктора
TEST(VectorTest, Constructor) {
    MyVector<int> vec;
    EXPECT_EQ(vec.size(), 0);
}
// Также проверим функцию добавления элемента в конец
// и получение элемента с использованием []
TEST(VectorTest, PushBackGetElemSize) {
    MyVector<int> vec;
    EXPECT_THROW(vec[0], std::out_of_range);
    vec.push_back(10);
    ASSERT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], 10);
    vec.push_back(20);
    int tmp = 30;
    vec.push_back(tmp);
    ASSERT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 10);
    EXPECT_EQ(vec[1], 20);
    EXPECT_EQ(vec[2], 30);
    EXPECT_THROW(vec[vec.size()], std::out_of_range);
    EXPECT_THROW(vec[-1], std::out_of_range);
}

// В фикстуре инициализируются два контейнера:
//  v1 - [0, 1, 2, 3, 4] 
//  v2 - пустой
// Тестирование фикстуры
TEST_F(VectorTestFixture, Fixture) {
    ASSERT_EQ(v1.size(), 5);
    for (std::size_t i = 0; i < v1.size(); i++) {
        EXPECT_EQ(v1[i], i);
    }
    ASSERT_EQ(v2.size(), 0);
}

// Тестирование вставки в начало
TEST_F(VectorTestFixture, PushFront) {
    v2.push_front(30);
    ASSERT_EQ(v2.size(), 1);
    EXPECT_EQ(v2[0], 30);
    v2.push_front(20);
    int tmp = 10;
    v2.push_front(tmp);
    ASSERT_EQ(v2.size(), 3);
    EXPECT_EQ(v2[0], 10);
    EXPECT_EQ(v2[1], 20);
    EXPECT_EQ(v2[2], 30);
}

// Тестирование вставки в середину
TEST_F(VectorTestFixture, PushMiddle) {
    auto index = v1.size() / 2;
    v1.insert(index, 10);
    ASSERT_EQ(v1.size(), 6);
    EXPECT_EQ(v1[index], 10);
    v1.insert(index, 20);
    ASSERT_EQ(v1.size(), 7);
    EXPECT_EQ(v1[index], 20);
    EXPECT_EQ(v1[index + 1], 10);
    int tmp = 30;
    index = v1.size() / 2;
    v1.insert(index, tmp);
    ASSERT_EQ(v1.size(), 8);
    EXPECT_EQ(v1[index], 30);
    EXPECT_EQ(v1[index + 1], 10);
    EXPECT_EQ(v1[index - 1], 20);

    EXPECT_THROW(v2.insert(1, 0), std::out_of_range);
    v2.insert(0, 0);
    ASSERT_EQ(v2.size(), 1);
    EXPECT_EQ(v2[0], 0);
}

// Тестирование удаления с конца
TEST_F(VectorTestFixture, PopBack) {
    v2.pop_back();
    ASSERT_EQ(v2.size(), 0);
    v1.pop_back();
    ASSERT_EQ(v1.size(), 4);
    EXPECT_EQ(v1[v1.size()-1], 3);
    v1.pop_back();
    v1.pop_back();
    ASSERT_EQ(v1.size(), 2);
    EXPECT_EQ(v1[1], 1);
    EXPECT_EQ(v1[0], 0);
}

// Тестирование удаления с начала
TEST_F(VectorTestFixture, PopFront) {
    v2.pop_front();
    ASSERT_EQ(v2.size(), 0);
    v1.pop_front();
    ASSERT_EQ(v1.size(), 4);
    EXPECT_EQ(v1[0], 1);
    v1.pop_front();
    v1.pop_front();
    ASSERT_EQ(v1.size(), 2);
    EXPECT_EQ(v1[0], 3);
    EXPECT_EQ(v1[1], 4);
}
// Тестирование конструкторов копирования
TEST_F(VectorTestFixture, CopyConstructor) {
  {
    MyVector<int> vec(v2);
    ASSERT_EQ(vec.size(), 0);
    ASSERT_EQ(vec.size(), v2.size());
  }
  {
    MyVector<int> vec(v1);
    ASSERT_EQ(vec.size(), 5);
    ASSERT_EQ(vec.size(), v1.size());
    for (std::size_t i = 0; i < v1.size(); i++) {
        EXPECT_EQ(v1[i], i);
        EXPECT_EQ(v1[i], vec[i]);
    }
  }
  {
    MyVector<int> vec;
    vec = v1;
    ASSERT_EQ(vec.size(), 5);
    ASSERT_EQ(vec.size(), v1.size());
    // Здесь дополнительно тестируем обращение к элементу через []
    for (std::size_t i = 0; i < v1.size(); i++) {
        EXPECT_EQ(v1[i], i);
        EXPECT_EQ(v1[i], vec[i]);
    }
  }
}

// Тестирование конструкторов перемещения
// Тестирование имеет смысл при условии корректности конструктора копирования
TEST_F(VectorTestFixture, MoveConstructor) {
  {
    MyVector<int> tmp(v2);
    MyVector<int> vec(std::move(tmp));
    ASSERT_EQ(vec.size(), 0);
    EXPECT_EQ(tmp.size(), 0);
  }
  {
    MyVector<int> tmp(v1);
    MyVector<int> vec(std::move(tmp));
    ASSERT_EQ(vec.size(), 5);
    EXPECT_EQ(tmp.size(), 0);
    // Здесь дополнительно тестируем обращение к элементу через []
    for (std::size_t i = 0; i < v1.size(); i++) {
        EXPECT_EQ(vec[i], i);
    }
  }
  {
    MyVector<int> tmp(v1);
    MyVector<int> vec;
    vec = std::move(tmp);
    ASSERT_EQ(vec.size(), 5);
    EXPECT_EQ(tmp.size(), 0);
    // Здесь дополнительно тестируем обращение к элементу через []
    for (std::size_t i = 0; i < v1.size(); i++) {
        EXPECT_EQ(vec[i], i);
    }
  }
}