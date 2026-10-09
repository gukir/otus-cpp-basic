#pragma once
#include "my_container.h"

template <typename T>
class MyDList : public MyContainer<T> {
    struct Node {
        Node* prev;
        T value;
        Node* next;
        Node(T val) : value(val), prev(nullptr), next(nullptr) {}
    };

public:
    // Конструктор
    MyDList()
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
    ~MyDList() override {
        clear();
    }

    // Конструктор копирования
    MyDList(const MyDList& copy) {
        if (copy.head_ == nullptr) return;
        for (Node* c = copy.head_; c; c = c->next)
            push_back(c->value);
    }
    // Конструктор перемещения
    MyDList(MyDList&& moved)
        : size_(moved.size_)
        , head_(moved.head_)
        , tail_(moved.tail_)
    {
        moved.size_ = 0;
        moved.head_ = nullptr;
        moved.tail_ = nullptr;
    }
    // Оператор присваивания через копию
    MyDList& operator=(MyDList copy){
        this->swap(copy);
        return *this;
    }
    // Вспомогательная функция для copy-and-swap
    void swap(MyDList& other) {
        std::swap(head_, other.head_);
        std::swap(tail_, other.tail_);
        std::swap(size_, other.size_);
    }
    // Оператор присваивания с перемещением
    MyDList& operator=(MyDList&& moved){
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

    // Вспомогательная функция для поиска элемента по индексу за O(N/2)
    Node* getNode(std::size_t index) const {
        if (index >= size_ || index < 0) return nullptr;

        Node* curr_node;
        // К какому концу индекс ближе, с того и начинаем движение
        if (index < size_ / 2) {
            curr_node = head_;
            for (std::size_t i = 0; i < index; ++i) curr_node = curr_node->next;
        } else {
            curr_node = tail_;
            for (std::size_t i = size_ - 1; i > index; --i) curr_node = curr_node->prev;
        }
        return curr_node;
    }

    // Добавление элемента по индексу
    void insert(std::size_t index, const T& value) override {
        if (index > size_ || index < 0) throw std::out_of_range("DList::insert");
        // Создадим новый узел
        Node* new_node = new Node{value};
        // При пустом списке
        if (head_ == nullptr) {
            head_ = tail_ = new_node;
        }
        // Если вставляем в начало
        else if (index == 0) {
            new_node->next = head_;
            head_->prev = new_node;
            head_ = new_node;
        }
        // Если вставляем в конец
        else if (index == size_) {
            tail_->next = new_node;
            new_node->prev = tail_;
            tail_ = new_node;
        }
        // Для других случаев
        else {
            Node* current = getNode(index);
            Node* previous = current->prev;

            new_node->next = current;
            new_node->prev = previous;

            previous->next = new_node;
            current->prev = new_node;
        }
        ++size_;
    }

    // Добавление элемента в конец контейнера
    void push_back(const T& value) override {insert(size_, value);}

    // Добавление элемента в начало контейнера
    void push_front(const T &value) override {insert(0, value);}

    // Удаление элемента по индексу
    void erase(std::size_t index) override {
        if (index >= size_ || index < 0) throw std::out_of_range("DList::erase");
        // Найдём узел для удаления
        Node* target = getNode(index);
        // Если удаляем единственный элемент
        if (head_ == tail_) {
            head_ = tail_ = nullptr;
        }
        // Если удаляем голову
        else if (target == head_) {
            head_ = head_->next;
            head_->prev = nullptr;
        }
        // Если удаляем хвост
        else if (target == tail_) {
            tail_ = tail_->prev;
            tail_->next = nullptr;
        }
        // В общем случае
        else {
            target->prev->next = target->next;
            target->next->prev = target->prev;
        }
        delete target;
        --size_;
    }

    // Геттер размера контейнера
    std::size_t size() const override { return size_; }

    // Возврат элемента контейнера
    T& operator[](std::size_t index) override {
        Node* node = getNode(index);
        return node->value;
    }
    const T& operator[](std::size_t index) const override {
        Node* node = getNode(index);
        return node->value;
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
        bool operator== (const Iterator& other) {
            return m_ptr == other.m_ptr;
        }
        bool operator!= (const Iterator& other) {
            return m_ptr != other.m_ptr;
        }
    private:
        Node* m_ptr;
    };
    Iterator begin()              {return Iterator(head_);}
    const Iterator begin() const  {return Iterator(head_);}
    Iterator end()                {return Iterator(nullptr);}
    const Iterator end() const    {return Iterator(nullptr);}

    // Вывод в поток
    void print(std::ostream& os) const override {
        os << '(';
        for (Iterator i = this->begin(); i != this->end(); i++){
            if (i != this->begin()) os << ", ";
            os << *i;
        }
        os << ')';
    }

    std::string name() const override {return "MyDList";}

private:
    Node* head_ = nullptr;
    Node* tail_ = nullptr;
    std::size_t size_ = 0;
};
