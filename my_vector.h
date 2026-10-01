#pragma once
#include <cstddef>
#include <ostream>

template <typename T>
class MyVector{
public:

    // Конструктор
    MyVector();

    // Деструктор
    ~MyVector();

    // Добавление элемента в конец контейнера
    void push_back(const T &value);



    // Геттер размера контейнера
    std::size_t size() const;

    // Возврат элемента контейнера
    const T& operator[](std::size_t ind) const;

private:
    std::size_t size_; // размер контейнера
    std::size_t capacity_; // вместимость контейнера
    T* data_; // указатель на данные

    // Расширение контейнера
    void reallocate();
};

// Перегрузка оператора вывода в поток
template <typename T>
std::ostream& operator<<(std::ostream& os, const MyVector<T>& vec);

#include "my_vector.tpp"
