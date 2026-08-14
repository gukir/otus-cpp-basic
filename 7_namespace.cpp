#include <iostream>

// Объявляем пространство имён algo
// Всё содержимое будет относиться к этому пространству имён
namespace algo {

    // Определение функции palindrome, которая:
    // - возвращает значение тип bool
    // - принимает один параметр типа std::string
    bool palindrome(std::string str) {

        std::cout << "Hello from palindrome example!" << std::endl;

        // Идём с противоположных концов строки, сравнивая символы
        bool result{true};
        for (int i = 0, j = str.size() - 1; i < j; i++, j--) {
            if (str[i] != str[j]) {
                result = false;
                break;
            }
        }
        return result;
    }

    int global_variable{42};

} // namespace algo

int global_variable{24};

int main() {

    std::string str = "98765432123456789";
    bool result = algo::palindrome(str);
    std::cout << std::boolalpha;
    std::cout << "palindrome(\"" << str << "\") = " << result << std::endl;

    std::cout << algo::palindrome("ParraP") << std::endl; // true
    std::cout << algo::palindrome("Parrap") << std::endl; // false

    // С префиксом algo - переменная из пространства имён algo
    std::cout << algo::global_variable << std::endl; // 42
    // Без префикса algo - переменная из глобального (или текущего) пространства имён
    std::cout << global_variable << std::endl; // 24

    return 0;
}