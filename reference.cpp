#include <iostream>

void foo(int& value) {
    value = 5;
}

int main() {
    int a = 1;
    int& b = a;

    std::cout << b << std::endl;
    b = 55;
    std::cout << a << std::endl;
    foo(a);
    std::cout << a << std::endl;
}