#include <iostream>

int main() {

    std::cout << "Hello from the \"Magic guess\" app!" << std::endl;

    int magic_number = 89;

    int guess{0};
    while(true) {
        std::cout << "Enter your guess (decimal value (0..100]): ";
        std::cin >> guess;

        if(guess <= 0) {
            std::cout << "Invalid input!" << std::endl;
            // Прерывает текущую итерацию и переходит к следующей (с начала тела цикла)
            continue;
        }

        if(guess == magic_number) {
            std::cout << "Success!" << std::endl;
            // Прерывает выполнение цикла полностью
            break;
        }

        std::cout << "Wrong guess! Next try." << std::endl;
    }


    return 0;
}