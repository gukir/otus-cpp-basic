#include <iostream>

// Функция принимает число и предлагает его угадать.
// Возвращает количество попыток, затраченных на угадывание.
int check_value(const int target_value) {

	int current_value = 0;
	int attempts = 0;

	std::cout << "Enter your guess:" << std::endl;

	do {
		attempts++;
		std::cin >> current_value;

        if (current_value > target_value) {
            std::cout << "target_value less than " << current_value << std::endl;
		}
        else if (current_value < target_value) {
            std::cout << "target_value greater than " << current_value << std::endl;
		}
		else {
			std::cout << "you win! attempts = " << attempts << std::endl;
			break;
		}

	} while(true);

	return attempts;
}
