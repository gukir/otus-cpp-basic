#include <iostream>
#include <iomanip>

// Определение функции pyramid, которая:
// - ничего не возвращает (void)
// - принимает один параметр типа int (height)
void pyramid(int height) {
    std::cout << "Hello from the pyramid function!" << std::endl;
    std::cout << "The height is: " << height << std::endl;

    // Символ для "фона"
    char empty_symb = ' ';
    // Символ для "рисования"
    char star_symb = '*';

    // Ширина основания пирамиды
    const int size = 2 * height - 1;
    for(int row{0}; row < height; ++row) {
        // Ширина текущего уровня пирамиды
        const int line_size = 2 * (height - row) - 1;

        // Выводим пустые символы
        for(int empty{0}; empty < row; empty++)
            std::cout << empty_symb;
        // Выводим звёздочки
        for(int stars{0}; stars < line_size; ++stars)
            std::cout << star_symb;
        // Выводим пустые символы
        for(int empty{line_size+row}; empty < size; empty++)
            std::cout << empty_symb;
        std::cout << std::endl;
    }

}

// Определение функции palindrome, которая:
// - возвращает значение тип bool
// - принимает один параметр типа std::string
bool palindrome(std::string str) {

    std::cout << "Hello from palindrome example!" << std::endl;

    // Идём с противоположных концов строки, сравнивая символы
    bool result{true};
    for(int i = 0, j = str.size() - 1; i < j; i++, j--) {
        if(str[i] != str[j]) {
            result = false;
            break;
        }
    }
    return result;
}




int main() {

    int height = 10;
    // вызов функции
    pyramid(height);

    return 0;
}