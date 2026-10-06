#pragma once
#include "my_container.h"

template <typename T>
class MySList : public MyContainer<T> {
    struct Node {
        T value;
        Node* next;
        Node(T val) : value(val), next(nullptr) {}
    };

public:
    // Конструктор
    MySList()
        : size_{0}
        , head_{nullptr}
        , tail_{nullptr}
    {}

    void clear(){
        // Начиная с головы освобождаем память каждого узла
        while (head_) {
            Node* current = head_->next;
            delete head_;
            head_ = current;
        }
        tail_ = nullptr;
        size_ = 0;
    }
    // Деструктор
    ~MySList() override {
        clear();
    }

    // Конструктор копирования
    MySList(const MySList& copy) {
        if (copy.head_ == nullptr) return;
        for (Node* c = copy.head_; c; c = c->next)
            push_back(c->value);
    }
    // Конструктор перемещения
    MySList(MySList&& moved)
        : size_(moved.size_)
        , head_(moved.head_)
        , tail_(moved.tail_)
    {
        moved.size_ = 0;
        moved.head_ = nullptr;
        moved.tail_ = nullptr;
    }
    // Оператор присваивания через копию
    MySList& operator=(MySList copy){
        this->swap(copy);
        return *this;
    }
    // Вспомогательная функция для copy-and-swap
    void swap(MySList& other) {
        std::swap(head_, other.head_);
        std::swap(tail_, other.tail_);
        std::swap(size_, other.size_);
    }
    // Оператор присваивания с перемещением
    MySList& operator=(MySList&& moved){
        if (this != &moved){//защита от перемещения в себя же
            // Сначала удаляем ранние данные
            clear();
            // Забираем из moved
            head_ = moved.head_;
            tail_ = moved.tail_;
            size_ = moved.size_;
            // Обнуляем moved
            moved.head_ = nullptr;
            moved.tail_ = nullptr;
            moved.size_ = 0;
        }
        return *this;
    }

    // Добавление элемента в конец контейнера
    void push_back(const T& value) override {
        // Создадим новый узел
        Node* node = new Node{value};
        // Если список не пустой (есть хвост)
        if (tail_) tail_->next = node; //То указываем на новый узел
        else head_ = node; // Иначе головой указываем на единственный узел
        // Перезаписываем указатель на хвост
        tail_ = node;
        ++size_;
    }

    // Добавление элемента по индексу
    void insert(std::size_t index, const T& value) override {
        if (index > size_) throw std::out_of_range("SList::insert");
        if (index == size_) { push_back(value); return; }
        // Для минимизации проверок вставку будим проводить с помощью указателя на указатель
        // Создадим новый узел
        Node* node = new Node{value};
        // Инициализируем указатель на указатель
        Node** curr_ref = &head_;
        // Сдвигаем его на index
        for (std::size_t i = 0; i < index; ++i)
            curr_ref = &((*curr_ref)->next);
        // Врезка элемента
        node->next = *curr_ref;
        *curr_ref = node;
        ++size_;
    }

    // Добавление элемента в начало контейнера
    void push_front(const T &value) {insert(0, value);}

    // Удаление элемента по индексу
    void erase(std::size_t index) override {
        if (index >= size_ || index < 0) throw std::out_of_range("SList::erase");
        // Удаление также будем производить с помощью указателя на указатель
        // Инициализируем указатель на указатель
        Node** curr_ref = &head_;
        // Перемещаемся к нужному индексу
        for (std::size_t i = 0; i < index; ++i)
            curr_ref = &(*curr_ref)->next;
        Node* target = *curr_ref;
        *curr_ref = target->next;
        // Если удаляем последний элемент, то необходимо обновить адрес хвоста
        if (tail_ == target) {
            tail_ = nullptr;
            for (Node* c = head_; c; c = c->next)
                if (!c->next) tail_ = c;
        }
        delete target;
        --size_;
    }

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
    std::size_t size() const override { return size_; }

    // Возврат элемента контейнера
    T& operator[](std::size_t index) override {
        Node* cur = head_;
        for (std::size_t i = 0; i < index; ++i) cur = cur->next;
        return cur->value;
    }
    const T& operator[](std::size_t index) const override {
        Node* cur = head_;
        for (std::size_t i = 0; i < index; ++i) cur = cur->next;
        return cur->value;
    }

    // Итераторы
    class Iterator {
    public:
        Iterator(Node* node) : m_ptr(node) {}
        T& operator*() const {return m_ptr->value;}
        // Перегрузка оператора инкремента
        Iterator& operator++() {
            if (m_ptr != nullptr) m_ptr = m_ptr->next;
            return *this;
        }
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
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
        Node* m_ptr;
    };
    Iterator begin()              {return Iterator(head_);}
    const Iterator begin() const  {return Iterator(head_);}
    Iterator end()                {return Iterator(nullptr);}
    const Iterator end() const    {return Iterator(nullptr);}

    friend std::ostream& operator<<(std::ostream& os, const MySList& slist){
        os << '(';

        for (Iterator i = slist.begin(); i != slist.end(); i++){
            if (i != slist.begin()) os << ", ";
            os << *i;
        }
        os << ')';
        return os;
    }

private:
    Node* head_ = nullptr;
    Node* tail_ = nullptr;
    std::size_t size_ = 0;
};
