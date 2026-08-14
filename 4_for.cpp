#include <iostream>

int main() {

    // Коэффициент восстановления скорости мяча при ударе
    double koeff{0.8};
    // Начальная высота падения мяча
    double height{100.0};
    // Ниже 0.1 высота нас не интересует
    const double min_height = 0.1;

    // for( initialization;  condition; expression )
    // initialization - секция объявления и/или инициализации (обычно счётчиков)
    // condition - условие, проверяет перед началом каждой итерации
    // expression - выражения (обычно со счётчиками), выполняется в конце каждой итерации

    for (int counter = 0; height > min_height; ++counter) {
        height *= koeff;
        std::cout << "counter = " << counter << " height = " << height << std::endl;
    }

    // Будем крутиться в цикле до ввода подходящего пароля
    for (std::string pass; pass != "SuperSecretPassword"; /*empty*/) {
        std::cout << "Enter the password: ";
        std::cin >> pass;
    }
    std::cout << "Success!" << std::endl;

    // Выведем все нечётные числа от 0 до 100
    for(int counter{0}; counter < 100; ++counter) {
        if (counter % 2 == 0) {
            // Остаток от деления == 0 - число чётное, пропускаем итерацию
            // Прерывает текущую итерацию и переходит к следующей (с начала тела цикла)
            continue;
        }
        // Эта строчка выполнится только для нечётных чисел
        std::cout << counter << ' ';
    }
    // Ошибка - переменная counter локальная для цикла for
    // counter += 0;


    std::cout << "Hello from the \"Magic guess\" app!" << std::endl;
    int magic_number = 89;
    for(int guess{0}; /*empty*/; /*empty*/) {
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
}