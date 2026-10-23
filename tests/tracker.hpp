#pragma once
#include <iostream>

struct Tracker {
    static inline int alive_count = 0; // Счетчик живых объектов
    int id;
    // Конструктор по умолчанию
    Tracker(int i) : id(i) { 
        ++alive_count; 
    }
    // Конструктор копирования
    Tracker(const Tracker&) { 
        ++alive_count; 
    }
    // Конструктор перемещения (важно noexcept для векторов!)
    Tracker(Tracker&&) noexcept { 
        ++alive_count; 
    }
    // Деструктор
    ~Tracker() { 
        --alive_count; 
    }
    // Операторы присваивания не меняют количество объектов,
    // но они нужны для корректной работы контейнера
    Tracker& operator=(const Tracker&) = default;
    Tracker& operator=(Tracker&&) noexcept = default;
    // Определим оператор вывода во избежание ошибки gtest
    friend std::ostream& operator<<(std::ostream& os, const Tracker& t) {
        return os << "Tracker(" << t.id << "(";
    }
};