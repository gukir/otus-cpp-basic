#include <iostream>

int func(int a, int b) {
    int sum = a + b;
    return sum;
}

int main() {
    int a = 5;
    int b = 6;
    int result = func(a, b);
    std::cout << "sum: " << result << std::endl;
}