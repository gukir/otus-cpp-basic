#pragma once
#include <memory>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <utility>


template <typename T>
MyVector<T>::MyVector()
    : size_{0}
    , capacity_{0}
    , data_{nullptr}
{}

template <typename T>
MyVector<T>::~MyVector(){
    // Вызываем деструктор каждого элемента контейнера
    for (std::size_t i = 0; i < size_; i++){
        data_[i].~T();
    }
    // Освобождаем ранее выделенную память
    ::operator delete(data_);
}

template <typename T>
MyVector<T>::MyVector(const MyVector& copy)
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

template <typename T>
MyVector<T>::MyVector(MyVector&& moved)
    : size_(moved.size_)
    , capacity_(moved.capacity_)
    , data_(moved.data_)
{
    moved.size_ = 0;
    moved.capacity_ = 0;
    moved.data_ = nullptr;
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& copy){
    if (this != &copy){//защита от копирования в себя же
        // Используем конструктор копирования во избежание дублирования кода
        MyVector tmp(copy);
        // Меняем местами данные с this
        std::swap(*this, tmp);
    }
    return *this;
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(MyVector&& moved){
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
        moved.capacity = 0;
    }
    return *this;
}

template <typename T>
void MyVector<T>::insert(std::size_t index, const T& value) {
    if (index > size_)
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

template <typename T>
void MyVector<T>::push_front(const T &value) {
    insert(0, value);
}

template <typename T>
void MyVector<T>::push_back(const T &value) {
    insert(size_, value);
}

template <typename T>
void MyVector<T>::erase(std::size_t ind) {
    if (ind >= size_)
        throw std::out_of_range("MyVector: индекс удаляемого элемента находится за пределами контейнера.");
    // Для удаления одного элемента из контейнера
    for (std::size_t i = ind; i + 1 < size_; ++i)
        // Сдвигаем все элементы правее его на одну позицию влево
        data_[i] = std::move(data_[i + 1]);
    // Удаляем последний элемент и декрементируем значение размера контейнера
    data_[--size_].~T();
}

template <typename T>
void MyVector<T>::erase(const std::size_t* indices, std::size_t count) {
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

template <typename T>
void MyVector<T>::reallocate(){
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

template <typename T>
std::size_t MyVector<T>::size() const{
    return size_;
}

template <typename T>
const T& MyVector<T>::operator[](std::size_t ind) const{
    return data_[ind];
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const MyVector<T>& vec){
    os << '(';
    for (std::size_t i = 0; i < vec.size(); i++){
        if (i > 0) os << ", ";
        os << vec[i];
    }
    os << ')';
    return os;
}
