#include <iostream>

int main() {

    int count = 10;

    bool condition = (count > 5) || (count == 5); // (count >= 5)

    // Цикл while - выполняется до тех пор, пока "condition == true"
    while( condition ) {
        std::cout << "This line is printed on the screen several times." << std::endl;
        --count;
        condition = (count > 5) || (count == 5);
    }
    // 6 раз, потому что: 10, 9, 8, 7, 6, 5 подпадают под условие

    // Вполне допустимо использовать условие явно - без отдельной
    // переменной condition
    while( (count > 5) || (count == 5) ) {
        std::cout << "This line will not be printed on the screen several times." << std::endl;
        --count;
    }
    // Здесь вывода не будет, потому что count уже < 5


    // Будем крутиться в цикле до ввода подходящего пароля
    std::string pass;
    while(pass != "SuperSecretPassword") {
        std::cout << "Enter the password: ";
        std::cin >> pass;
    }
    std::cout << "Success!" << std::endl;


    // Коэффициент восстановления скорости мяча при ударе
    double koeff{0.8};
    // Начальная высота падения мяча
    double height{100.0};
    // Ниже 0.1 высота нас не интересует
    const double min_height = 0.1;
    // Счётчик отскоков
    int counter = 0;
    while( height > min_height ) {
        ++counter;
        height *= koeff;
        std::cout << "counter = " << counter << " height = " << height << std::endl;
    }

    
}