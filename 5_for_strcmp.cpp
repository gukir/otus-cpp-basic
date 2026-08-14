#include <iostream>
#include <string>

int main() {

    std::cout << "Hello from the strcmp app!" << std::endl;

    std::string first;
    std::cout << "Enter the first string: " << std::endl;
    std::cin >> first;

    std::string second;
    std::cout << "Enter the second string: " << std::endl;
    std::cin >> second;

    if (first.size() != second.size()) {
        std::cout << "Strings are different because of size!" << std::endl;
        std::cout << "first size: " << first.size() << std::endl;
        std::cout << "second size: " << second.size() << std::endl;
        return 0;
    }

    for (size_t i = 0; i < first.size(); ++i) {
        if (first[i] != second[i]) {
            std::cout << "Strings are different because of " << i << " symbol!" << std::endl;
            std::cout << "first[" << i << "] = " << first[i] << std::endl;
            std::cout << "second[" << i << "] = " << second[i] << std::endl;
            return 0;
        }
    }

    std::cout << "Strings are equal!" << std::endl;

    return 0;
}