#include <gtest/gtest.h>
#include "vector_fixture.hpp"
#include "tracker.hpp"

// Перед запуском тестов с использованием фикстур
// проверим функциональность конструктора
TEST(Vector, Constructor) {
    MyVector<int> vec;
    EXPECT_EQ(vec.size(), 0);
}
// Также проверим функцию добавления элемента в конец
// и получение элемента с использованием []
TEST(Vector, PushBackGetElemSize) {
    MyVector<int> vec;
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
}

// В фикстуре инициализируются два контейнера:
//  v1 - [0, 1, 2, 3, 4] 
//  v2 - пустой
// Тестирование фикстуры
TEST_F(VectorF, Fixture) {
    ASSERT_EQ(v1.size(), 5);
    for (std::size_t i = 0; i < v1.size(); i++) {
        EXPECT_EQ(v1[i], i);
    }
    ASSERT_EQ(v2.size(), 0);
}

// Тестирование обращения к элементу вне диапазона
TEST_F(VectorF, OutOfRange) {
    EXPECT_THROW(v1[v1.size()], std::out_of_range);
    EXPECT_THROW(v1[-1], std::out_of_range);
    EXPECT_THROW(v2[0], std::out_of_range); 
}

// Тестирование вставки в начало
TEST_F(VectorF, PushFront) {
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
TEST_F(VectorF, PushMiddle) {
    auto index = v1.size() / 2;
    v1.insert(index, 10);
    ASSERT_EQ(v1.size(), 6);
    EXPECT_EQ(v1[index], 10);
    EXPECT_EQ(v1[index - 1], 1);
    EXPECT_EQ(v1[index + 1], 2);
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
TEST_F(VectorF, PopBack) {
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
TEST_F(VectorF, PopFront) {
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

// Тестирование удаления с середины
TEST_F(VectorF, PopMiddle) {
    auto index = v1.size() / 2;
    v1.erase(index);
    ASSERT_EQ(v1.size(), 4);
    EXPECT_EQ(v1[index], 3);
    EXPECT_EQ(v1[index - 1], 1);
    v1.erase(index);
    index = v1.size() / 2;
    v1.erase(index);
    ASSERT_EQ(v1.size(), 2);
    EXPECT_EQ(v1[0], 0);
    EXPECT_EQ(v1[1], 4);
    EXPECT_THROW(v2.erase(2), std::out_of_range);
    EXPECT_THROW(v2.erase(-1), std::out_of_range);

    EXPECT_THROW(v2.erase(0), std::out_of_range);
}

// Тестирование удаления нескольких элементов
TEST_F(VectorF, MultiplyErase) {
  {
      MyVector<int> tmp(v1);
      std::size_t for_del[] = {1, 3};
      tmp.erase(for_del, static_cast<std::size_t>(sizeof(for_del) / sizeof(for_del[0])));
      ASSERT_EQ(tmp.size(), 3);
      EXPECT_EQ(tmp[0], 0);
      EXPECT_EQ(tmp[1], 2);
      EXPECT_EQ(tmp[2], 4);
  }
  {
      MyVector<int> tmp(v1);
      std::size_t for_del[] = {2, 4, 0};
      tmp.erase(for_del, static_cast<std::size_t>(sizeof(for_del) / sizeof(for_del[0])));
      ASSERT_EQ(tmp.size(), 2);
      EXPECT_EQ(tmp[0], 1);
      EXPECT_EQ(tmp[1], 3);
  }
  {
      MyVector<int> tmp(v1);
      std::size_t for_del[] = {2, 4, 6};
      EXPECT_THROW(tmp.erase(for_del, static_cast<std::size_t>(sizeof(for_del) / sizeof(for_del[0]))), std::out_of_range);
  }
}

// Тестирование итераторов
TEST_F(VectorF, Iterators) {
    auto it = v1.begin();
    EXPECT_EQ(*it, v1[0]);
    for (std::size_t i = 0; i < v1.size(); i++){
        EXPECT_EQ(*it, v1[i]);
        it++;
    }
    EXPECT_EQ(it, v1.end());
  
    EXPECT_EQ(v2.begin(), nullptr);
    EXPECT_EQ(v2.begin(), v2.end());
}

// Тестирование конструкторов копирования
TEST_F(VectorF, CopyConstructor) {
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

// Тестирование деструктора
TEST(Vector, Destructor){
    // Сброс счетчика
    Tracker::alive_count = 0;
    {
        MyVector<Tracker> vec;
        int num = 5;
        for(int i = 0; i < num; i++){
            vec.push_back(i);
        }
        EXPECT_EQ(Tracker::alive_count, num);
    }
    EXPECT_EQ(Tracker::alive_count, 0); 
}

// Тестирование конструкторов перемещения
TEST_F(VectorF, MoveConstructor) {
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