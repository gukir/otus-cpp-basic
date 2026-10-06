#pragma once
#include <cstddef>
#include <ostream>

template <typename T>
class MyContainer{
public:
    // Деструктор
    virtual ~MyContainer() = default;

    // Добавление элемента по индексу
    virtual void insert(std::size_t index, const T& value) = 0;
    // Добавление элемента в конец контейнера
    virtual void push_back(const T &value) = 0;
    // Удаление элемента по индексу
    virtual void erase(std::size_t ind) = 0;
    // Геттер размера контейнера
    virtual std::size_t size() const = 0;

    // Возврат элемента контейнера
    virtual T& operator[](std::size_t ind) = 0;
    virtual const T& operator[](std::size_t ind) const = 0;
};
