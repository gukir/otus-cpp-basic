#include <iostream>
#include <vector>
#include <cstddef>
#include <cstdint>
#include <cstring>

// Базовый класс. Хранит ровно 1 байт (условный idшник)
struct Entity {
public:
    Entity() = default;
    Entity(uint8_t i) : id{i} {}

    uint8_t id{255};
};

using Color = uint32_t;

// Фигура, наследник Entity. Дополнительно хранит цвет (в виде числа, 4 байта)
struct Shape: public Entity {
public:
    Shape() = default;
    Shape(uint8_t id, Color c) : Entity{id}, color{c} {}

    Color color{};
    // uint8_t id - унаследовано от Entity, к нему можно обратиться
};

void test() {
    Entity e;
    e.id; // Ожидаемо доступно

    Shape s;
    s.color; // Ожидаемо доступно
    s.id; // Унаследовано от Entity, поэтому доступно
}

// Квадрат, наследник Shape. Дополнительно хранит длину стороны
struct Square: public Shape {
public:
    Square() = default;
    Square(uint8_t id, Color color, double l) : Shape(id, color), length{l} {}

    double length{};
};








void printSize() {
    // По размеру косвенно видно, что каждый дочерний класс включает
    // данные родительского.
    // sizeof(Shape) > sizeof(Entity) + sizeof(Color) из-за выравнивания
    // по умолчанию до границы 4 байта
    std::cout   << "sizeof(Entity) " << sizeof(Entity) << std::endl
                << "sizeof(Shape) "  << sizeof(Shape) << std::endl
                << "sizeof(Square) " << sizeof(Square) << std::endl;
}

void printAddress(const char* name, const void* ptr) {
    std::cout << "Address of " << name << " is " << ptr << std::endl;
}

void printAddresses(const Square& square) {
    // Указатель на объекты базового и дочерних классов совпадают,
    // т.к. наследники - "добавка к концу базового"
    printAddress("Square", &square);
    printAddress("Shape (static_cast)", static_cast<const Shape*>(&square));
    printAddress("Entity (static_cast)", static_cast<const Entity*>(&square));

    printAddress("id ", &square.id);
    printAddress("color ", &square.color);
    printAddress("length ", &square.length);
}

void test_print() {
    Square square{111, 3, 49.2};
    std::cout << "square: length=" << square.length << " color=" << square.color << " id=" << square.id << std::endl;

    printSize();
    printAddresses(square);
}

// Square square; // &square == 0
//          &square.id == 0
//          &square.color == 0 + sizeof(square.id) == 4
//          &square.length == 0 + sizeof(square.id) + sizeof(square.color) == 8






struct BaseStruct {
    int base_value{};
};

struct PublicDerivedStruct : BaseStruct {
    void test() {
        base_value; // Доступно, можно пользоваться
    }
// Унаследовано публично
/*
public:
    int base_value{};
*/
};
void publicDerivedStructTest() {
    PublicDerivedStruct s;
    s.base_value; // Доступно, можно пользоваться
}


struct PrivateDerivedStruct : private BaseStruct {
    void test() {
        base_value; // Доступно, потому что наследование
    }
// Унаследовано приватно
/*
private:
    int base_value{};
*/
};
void privateDerivedStructTest() {
    PrivateDerivedStruct s;
    // s.base_value;  // А вот тут уже недоступно, потому что наследование приватное
}









int main() {
    test_print();
}