#include <cstdlib>
#include <ctime>

// Функция возвращает случайное целое число от 0 до max_value
int random_value(const int max_value) {

	std::srand(std::time(nullptr)); // use current time as seed for random generator

    int random_value = std::rand() % max_value;

    return random_value;
}
