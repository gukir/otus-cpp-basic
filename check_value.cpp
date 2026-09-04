#include <iostream>
#include <string>

// Функция принимает число и предлагает его угадать.
// Возвращает количество попыток, затраченных на угадывание.
int check_value(const int target_value) {

	int current_value = 0;
    std::string input;
	int attempts = 0;

	std::cout << "Enter your guess:" << std::endl;

	do {
		attempts++;
        std::cin >> input;
        current_value = std::stoi(input);

        if (current_value > target_value) {
            std::cout << "less than " << current_value << std::endl;
		}
        else if (current_value < target_value) {
            std::cout << "greater than " << current_value << std::endl;
		}
		else {
			std::cout << "you win! attempts = " << attempts << std::endl;
			break;
		}

	} while(true);

	return attempts;
}
