#pragma once
#include <cstddef>
#include <ostream>
#include <algorithm>
#include <memory>

template <typename T>
class MyContainer{
public:
    // Деструктор
    virtual ~MyContainer() = default;

    // Добавление элемента по индексу
    virtual void insert(std::size_t index, const T& value) = 0;
    // Добавление элемента в конец контейнера
    virtual void push_back(const T &value) = 0;
    // Добавление элемента в начало контейнера
    virtual void push_front(const T &value) = 0;
    // Удаление элемента по индексу
    virtual void erase(std::size_t ind) = 0;
    // Удаление элемента по индексам
    void erase(const std::size_t* indices, std::size_t count) {
        // Выходим, если ничего удалять не нужно
        if (count == 0) return;

        // Выделяем память и копируем массив индексов, сортируем
        std::unique_ptr<std::size_t[]> sorted_indices(new std::size_t[count]);
        std::copy(indices, indices + count, sorted_indices.get());
        std::sort(sorted_indices.get(), sorted_indices.get() + count);

        // Удаляем по одному, начиная с последнего индекса в отсортированном массиве
        for (std::size_t i = count; i-- > 0; )
            erase(sorted_indices[i]);
    }
    // Геттер размера контейнера
    virtual std::size_t size() const = 0;

    // Возврат элемента контейнера
    virtual T& operator[](std::size_t ind) = 0;
    virtual const T& operator[](std::size_t ind) const = 0;
    // Вывод в поток
    virtual void print(std::ostream& os) const = 0;
    // Перегрузка оператора вывода в поток
    friend std::ostream& operator<<(std::ostream& os, const MyContainer& container) {
        container.print(os);
        return os;
    }
    // Строка имени класса
    virtual std::string name() const = 0;
};
