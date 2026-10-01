#pragma once
#include <memory>
#include <iostream>

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
void MyVector<T>::push_back(const T &value) {
    if (size_ == capacity_) reallocate();
    new (data_ + size_++) T(value);
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
