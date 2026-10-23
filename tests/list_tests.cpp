#include <gtest/gtest.h>
#include "list_fixture.hpp"
#include "tracker.hpp"

// Перед запуском тестов с использованием фикстур
// проверим функциональность конструктора
TEST(List, Constructor) {
    MySList<int> sl;
    EXPECT_EQ(sl.size(), 0);
}
// Также проверим функцию добавления элемента в конец
// и получение элемента с использованием []
TEST(List, PushBackGetElemSize) {
    MySList<int> sl;
    sl.push_back(10);
    ASSERT_EQ(sl.size(), 1);
    EXPECT_EQ(sl[0], 10);
    sl.push_back(20);
    int tmp = 30;
    sl.push_back(tmp);
    ASSERT_EQ(sl.size(), 3);
    EXPECT_EQ(sl[0], 10);
    EXPECT_EQ(sl[1], 20);
    EXPECT_EQ(sl[2], 30);
}

// В фикстуре инициализируются два контейнера:
//  l1 - [0, 1, 2, 3, 4] 
//  l2 - пустой
// Тестирование фикстуры
TEST_F(ListF, Fixture) {
    ASSERT_EQ(l1.size(), 5);
    for (std::size_t i = 0; i < l1.size(); i++) {
        EXPECT_EQ(l1[i], i);
    }
    ASSERT_EQ(l2.size(), 0);
}

// Тестирование обращения к элементу вне диапазона
TEST_F(ListF, OutOfRange) {
    EXPECT_THROW(l1[l1.size()], std::out_of_range);
    EXPECT_THROW(l1[-1], std::out_of_range);
    EXPECT_THROW(l2[0], std::out_of_range); 
}

// Тестирование вставки в начало
TEST_F(ListF, PushFront) {
    l2.push_front(30);
    ASSERT_EQ(l2.size(), 1);
    EXPECT_EQ(l2[0], 30);
    l2.push_front(20);
    int tmp = 10;
    l2.push_front(tmp);
    ASSERT_EQ(l2.size(), 3);
    EXPECT_EQ(l2[0], 10);
    EXPECT_EQ(l2[1], 20);
    EXPECT_EQ(l2[2], 30);
}

// Тестирование вставки в середину
TEST_F(ListF, PushMiddle) {
    auto index = l1.size() / 2;
    l1.insert(index, 10);
    ASSERT_EQ(l1.size(), 6);
    EXPECT_EQ(l1[index], 10);
    EXPECT_EQ(l1[index - 1], 1);
    EXPECT_EQ(l1[index + 1], 2);
    l1.insert(index, 20);
    ASSERT_EQ(l1.size(), 7);
    EXPECT_EQ(l1[index], 20);
    EXPECT_EQ(l1[index + 1], 10);
    int tmp = 30;
    index = l1.size() / 2;
    l1.insert(index, tmp);
    ASSERT_EQ(l1.size(), 8);
    EXPECT_EQ(l1[index], 30);
    EXPECT_EQ(l1[index + 1], 10);
    EXPECT_EQ(l1[index - 1], 20);

    EXPECT_THROW(l2.insert(1, 0), std::out_of_range);
    l2.insert(0, 0);
    ASSERT_EQ(l2.size(), 1);
    EXPECT_EQ(l2[0], 0);
}

// Тестирование удаления с конца
TEST_F(ListF, PopBack) {
    l2.pop_back();
    ASSERT_EQ(l2.size(), 0);
    l1.pop_back();
    ASSERT_EQ(l1.size(), 4);
    EXPECT_EQ(l1[l1.size()-1], 3);
    l1.pop_back();
    l1.pop_back();
    ASSERT_EQ(l1.size(), 2);
    EXPECT_EQ(l1[1], 1);
    EXPECT_EQ(l1[0], 0);
}

// Тестирование удаления с начала
TEST_F(ListF, PopFront) {
    l2.pop_front();
    ASSERT_EQ(l2.size(), 0);
    l1.pop_front();
    ASSERT_EQ(l1.size(), 4);
    EXPECT_EQ(l1[0], 1);
    l1.pop_front();
    l1.pop_front();
    ASSERT_EQ(l1.size(), 2);
    EXPECT_EQ(l1[0], 3);
    EXPECT_EQ(l1[1], 4);
}

// Тестирование удаления с середины
TEST_F(ListF, PopMiddle) {
    auto index = l1.size() / 2;
    l1.erase(index);
    ASSERT_EQ(l1.size(), 4);
    EXPECT_EQ(l1[index], 3);
    EXPECT_EQ(l1[index - 1], 1);
    l1.erase(index);
    index = l1.size() / 2;
    l1.erase(index);
    ASSERT_EQ(l1.size(), 2);
    EXPECT_EQ(l1[0], 0);
    EXPECT_EQ(l1[1], 4);
    EXPECT_THROW(l2.erase(2), std::out_of_range);
    EXPECT_THROW(l2.erase(-1), std::out_of_range);

    EXPECT_THROW(l2.erase(0), std::out_of_range);
}

// Тестирование удаления нескольких элементов
TEST_F(ListF, MultiplyErase) {
  {
      MySList<int> tmp(l1);
      std::size_t for_del[] = {1, 3};
      tmp.erase(for_del, static_cast<std::size_t>(sizeof(for_del) / sizeof(for_del[0])));
      ASSERT_EQ(tmp.size(), 3);
      EXPECT_EQ(tmp[0], 0);
      EXPECT_EQ(tmp[1], 2);
      EXPECT_EQ(tmp[2], 4);
  }
  {
      MySList<int> tmp(l1);
      std::size_t for_del[] = {2, 4, 0};
      tmp.erase(for_del, static_cast<std::size_t>(sizeof(for_del) / sizeof(for_del[0])));
      ASSERT_EQ(tmp.size(), 2);
      EXPECT_EQ(tmp[0], 1);
      EXPECT_EQ(tmp[1], 3);
  }
  {
      MySList<int> tmp(l1);
      std::size_t for_del[] = {2, 4, 6};
      EXPECT_THROW(tmp.erase(for_del, static_cast<std::size_t>(sizeof(for_del) / sizeof(for_del[0]))), std::out_of_range);
  }
}

// Тестирование итераторов
TEST_F(ListF, Iterators) {
    auto it = l1.begin();
    EXPECT_EQ(*it, l1[0]);
    for (std::size_t i = 0; i < l1.size(); i++){
        EXPECT_EQ(*it, l1[i]);
        it++;
    }
    EXPECT_EQ(it, l1.end());
  
    EXPECT_EQ(l2.begin(), nullptr);
    EXPECT_EQ(l2.begin(), l2.end());
}

// Тестирование конструкторов копирования
TEST_F(ListF, CopyConstructor) {
  {
    MySList<int> sl(l2);
    ASSERT_EQ(sl.size(), 0);
    ASSERT_EQ(sl.size(), l2.size());
  }
  {
    MySList<int> sl(l1);
    ASSERT_EQ(sl.size(), 5);
    ASSERT_EQ(sl.size(), l1.size());
    for (std::size_t i = 0; i < l1.size(); i++) {
        EXPECT_EQ(l1[i], i);
        EXPECT_EQ(l1[i], sl[i]);
    }
  }
  {
    MySList<int> sl;
    sl = l1;
    ASSERT_EQ(sl.size(), 5);
    ASSERT_EQ(sl.size(), l1.size());
    // Здесь дополнительно тестируем обращение к элементу через []
    for (std::size_t i = 0; i < l1.size(); i++) {
        EXPECT_EQ(l1[i], i);
        EXPECT_EQ(l1[i], sl[i]);
    }
  }
}

// Тестирование деструктора
TEST(List, Destructor){
    // Сброс счетчика
    Tracker::alive_count = 0;
    {
        MySList<Tracker> sl;
        int num = 5;
        for(int i = 0; i < num; i++){
            sl.push_back(i);
        }
        EXPECT_EQ(Tracker::alive_count, num);
    }
    EXPECT_EQ(Tracker::alive_count, 0); 
}

// Тестирование конструкторов перемещения
TEST_F(ListF, MoveConstructor) {
  {
    MySList<int> tmp(l2);
    MySList<int> sl(std::move(tmp));
    ASSERT_EQ(sl.size(), 0);
    EXPECT_EQ(sl.size(), 0);
  }
  {
    MySList<int> tmp(l1);
    MySList<int> sl(std::move(tmp));
    ASSERT_EQ(sl.size(), 5);
    EXPECT_EQ(tmp.size(), 0);
    // Здесь дополнительно тестируем обращение к элементу через []
    for (std::size_t i = 0; i < l1.size(); i++) {
        EXPECT_EQ(sl[i], i);
    }
  }
  {
    MySList<int> tmp(l1);
    MySList<int> sl;
    sl = std::move(tmp);
    ASSERT_EQ(sl.size(), 5);
    EXPECT_EQ(tmp.size(), 0);
    // Здесь дополнительно тестируем обращение к элементу через []
    for (std::size_t i = 0; i < l1.size(); i++) {
        EXPECT_EQ(sl[i], i);
    }
  }
}