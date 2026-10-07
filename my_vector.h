#pragma once
#include "my_container.h"
#include <iostream>
#include <stdexcept>
#include <utility>

template <typename T>
class MyVector : public MyContainer<T>{
public:
    // Конструктор
    MyVector()
        : size_{0}
        , capacity_{0}
        , data_{nullptr}
    {}

    // Деструктор
    ~MyVector() override{
        // Вызываем деструктор каждого элемента контейнера
        for (std::size_t i = 0; i < size_; i++){
            data_[i].~T();
        }
        // Освобождаем ранее выделенную память
        ::operator delete(data_);
    }

    // Конструктор копирования
    MyVector(const MyVector& copy)
        : size_(copy.size_)
        , capacity_(copy.capacity_)
    {
        // Выделяем новую область памяти и копируем значения из старой
        if(capacity_ > 0){
            data_ = static_cast<T*>(:: operator new(capacity_ * sizeof(T)));
            for(std::size_t i = 0; i < size_; i++)
                new (data_ + i) T(copy.data_[i]);
        }
    }
    // Конструктор перемещения
    MyVector(MyVector&& moved)
        : size_(moved.size_)
        , capacity_(moved.capacity_)
        , data_(moved.data_)
    {
        moved.size_ = 0;
        moved.capacity_ = 0;
        moved.data_ = nullptr;
    }
    // Оператор присваивания через копию
    MyVector& operator=(MyVector copy){
        this->swap(copy);
        return *this;
    }
    // Вспомогательная функция для copy-and-swap
    void swap(MyVector& other) {
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(data_, other.data_);
    }
    // Оператор присваивания с перемещением
    MyVector& operator=(MyVector&& moved){
        if (this != &moved){//защита от перемещения в себя же
            // Сначала удаляем ранние данные
            for (std::size_t i = 0; i < size_; i++)
                data_[i].~T();
            ::operator delete(data_);
            // Забираем из moved
            data_ = moved.data_;
            size_ = moved.size_;
            capacity_ = moved.capacity_;
            // Обнуляем moved
            moved.data_ = nullptr;
            moved.size_ = 0;
            moved.capacity_ = 0;
        }
        return *this;
    }

    // Добавление элемента по индексу
    void insert(std::size_t index, const T& value) {
        if (index > size_ || index < 0)
            throw std::out_of_range("MyVector: индекс вставки находится за пределами контейнера.");
        // Раздуваем вместимость, если достигли предела
        if (size_ == capacity_) reallocate();
        // Если индекс вставки равен размеру контейнера, то вставляем в конец
        if (index == size_) {
            new (data_ + size_) T(value);
        } else {
            // Иначе сдвигаем правую от индекса чать в право на один элемент
            new (data_ + size_) T(std::move(data_[size_ - 1]));
            for (std::size_t i = size_ - 1; i > index; i--)
                data_[i] = std::move(data_[i-1]);
            // И вписываем в образовавшуюся дырку значение
            data_[index] = value;
        }
        // Увеличиваем значение размера контейнера
        size_++;
    }
    // Добавление элемента в начало контейнера
    void push_front(const T &value) {insert(0, value);}
    // Добавление элемента в конец контейнера
    void push_back(const T &value) override {insert(size_, value);}

    // Удаление элемента по индексу
    void erase(std::size_t ind) override {
        if (ind >= size_ || ind < 0)
            throw std::out_of_range("MyVector: индекс удаляемого элемента находится за пределами контейнера.");
        // Для удаления одного элемента из контейнера
        for (std::size_t i = ind; i + 1 < size_; ++i)
            // Сдвигаем все элементы правее его на одну позицию влево
            data_[i] = std::move(data_[i + 1]);
        // Удаляем последний элемент и декрементируем значение размера контейнера
        data_[--size_].~T();
    }

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
        bool operator== (const Iterator& other) {
            return m_ptr == other.m_ptr;
        }
        bool operator!= (const Iterator& other) {
            return m_ptr != other.m_ptr;
        }
    private:
        T* m_ptr;
    };
    Iterator begin()              {return Iterator(data_);}
    const Iterator begin() const  {return Iterator(data_);}
    Iterator end()                {return Iterator(data_ + size_);}
    const Iterator end() const    {return Iterator(data_ + size_);}

    // Вывод в поток
    void print(std::ostream& os) const override {
        os << '(';
        for (std::size_t i = 0; i < this->size(); i++){
            if (i > 0) os << ", ";
            os << data_[i];
        }
        os << ')';
    }

    std::string name() const override {return "MyVector";}

private:
    std::size_t size_; // размер контейнера
    std::size_t capacity_; // вместимость контейнера
    T* data_; // указатель на данные

    // Расширение контейнера
    void reallocate(){
        // Раздуваем вдвое вместимость контейнера
        std::size_t new_capacity = capacity_ ? capacity_ * 2 : 1;
        // Выделяем новую память
        T* new_data = static_cast<T*>(::operator new(new_capacity * sizeof(T)));
        // Для каждого элемента контейнера:
        for (std::size_t i = 0; i < size_; i++) {
            // Вызываем конструктор элемента нового контейнера и перемещаем данные элемента из старого
            new (new_data + i) T(std::move(data_[i]));
            // Вызываем деструктор элемента старого контейнера
            data_[i].~T();
        }
        // Освобождаем память, ранее выделенную под старый контейнер
        ::operator delete(data_);
        // Присваиваем адрес новой памяти
        data_ = new_data;
        // Присваиваем новое значение вместимости
        capacity_ = new_capacity;
    }
};
