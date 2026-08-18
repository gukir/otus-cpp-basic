#include <array>
#include <iostream>

void bytesPlay() {
    int number = 256;
    unsigned char *bytes = reinterpret_cast<unsigned char *>(&number);

    for (size_t i = 0; i < sizeof(number); ++i) {
        std::cout << i << ": " << static_cast<int>(bytes[i]) << std::endl;
    }
    bytes[0] = 255;
    std::cout << number << std::endl;
}

void foo(int *ptr) { /*nothing*/ }

void array() {
    int array[4] = {1, 2, 3, 4};
    foo(array);

    int *ptr = array;

    std::cout << ptr[2] << " vs " << array[2] << std::endl;
    std::cout << *(array + 2) << std::endl;
}

int *dangerZone() {
    int array[4] = {1, 2, 3, 4};
    std::cout << "array[4]: " << array[4] << std::endl;

    int *begin = array;
    int *end = begin + 4;
    std::cout << "begin < end: " << std::boolalpha << (begin < end) << std::endl;

    int a = 1, b = 2;
    std::cout << "&a < &b: " << std::boolalpha << (&a < &b) << std::endl;

    *(&b + 1) = 5;
    std::cout << a << std::endl;
    return array;
}

int main() {
    bytesPlay();
    array();
    // dangerZone();
}
