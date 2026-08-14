// Для std::cout, std::cin, std::endl;
#include <iostream>
// Для std::setprecision()
#include <iomanip>
// Для std::string
#include <string>

int main() {

    int i_value{-20 / 3};

    // Инициализация в {} скобках более строгая, чем через =
    // Здесь компилятор будет жаловаться, что unsigned-переменную пытаемся
    // инициализировать отрицательным числом.
    // Error - conversion from 'int' to 'unsigned int'
    // unsigned int ui_value{-20 / 3};

    // Но мы всё равно это сделаем, чтобы посмотреть - что получится.
    unsigned int ui_value = -20 / 3;

    // 20.0 даёт понять компилятору, что мы хотим работать с числами с плавающей точкой
    // а не с целыми.
    float f_value{20.0 / 3};
    double d_value{20.0 / 3};

    std::cout << std::setprecision(20);

    std::cout << "i_value = " << i_value << std::endl;
    std::cout << "ui_value = " << ui_value << std::endl;
    std::cout << "f_value = " << f_value << std::endl;
    std::cout << "d_value = " << d_value << std::endl;

    int age{0};
    std::cout << "Press age, please: ";
    std::cin >> age;

    if(age < 18) {
        std::cout << "Restricted area!" << std::endl;
        return -1;
    }
    std::cout << "Ok" << std::endl;

    return 0;
}