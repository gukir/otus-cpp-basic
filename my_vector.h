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

    // Конструктор копирования
    MyVector(const MyVector& copy);
    // Конструктор перемещения
    MyVector(MyVector&& moved);
    // Оператор присваивания через копию
    MyVector& operator=(const MyVector& copy);
    // Оператор присваивания с перемещением
    MyVector& operator=(MyVector&& moved);

    // Добавление элемента по индексу
    void insert(std::size_t index, const T& value);
    // Добавление элемента в начало контейнера
    void push_front(const T &value) {insert(0, value);}
    // Добавление элемента в конец контейнера
    void push_back(const T &value) {insert(size_, value);}

    // Удаление элемента по индексу
    void erase(std::size_t ind);

    // Удаление элемента по индексам
    void erase(const std::size_t* indices, std::size_t count);

    // Геттер размера контейнера
    std::size_t size() const {return size_;}

    // Возврат элемента контейнера
    T& operator[](std::size_t ind) {return data_[ind];}
    const T& operator[](std::size_t ind) const {return data_[ind];}

    // Итераторы
    class Iterator {
    public:
        Iterator(T* ptr) : m_ptr(ptr) {}
        T& operator*() const {return *m_ptr;}
        // Перегрузка оператора инкремента
        Iterator& operator++() {
            m_ptr++;
            return *this;
        }
        Iterator operator++(int) {
            Iterator tmp = *this;
            m_ptr++;
            return tmp;
        }
        // Операторы сравнения
        friend bool operator== (const Iterator& a, const Iterator& b) {
            return a.m_ptr == b.m_ptr;
        }
        friend bool operator!= (const Iterator& a, const Iterator& b) {
            return a.m_ptr != b.m_ptr;
        }
    private:
        T* m_ptr;
    };
    Iterator begin()              {return Iterator(data_);}
    const Iterator begin() const  {return Iterator(data_);}
    Iterator end()                {return Iterator(data_ + size_);}
    const Iterator end() const    {return Iterator(data_ + size_);}

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
