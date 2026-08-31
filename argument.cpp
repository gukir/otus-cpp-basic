#include <iostream>
#include <string>

// Функция принимает аргументы командной строки и, в случае отсутствия ошибок, возвращает максимальное значение случайного числа.
// При наличии флага -table возвращаемое значение устанавливается в 0.
// В случае наличия недопустимых флагов или значений возвращается -1.
int argument(int argc, char** argv) {
    int max_value = 100;
    if (argc > 1) {
        std::string arg1_value{ argv[1] };
        if (arg1_value == "-max") {
            if (argc < 3) {
                std::cout << "Wrong usage! The argument '-max' requires some value!" << std::endl;
                max_value = -1;
            } else {
                max_value = std::stoi(argv[2]);
                if (max_value < 1) {
                    std::cout << "Wrong max value! The '-max' value must be more than 0!" << std::endl;
                    max_value = -1;
                }
            }
        } else if (arg1_value == "-table") {
            if (argc > 2) {
                std::cout << "Wrong usage! The argument '-table' doesn't require any values!" << std::endl;
                max_value = -1;
            } else {
                max_value = 0;
            }
        } else if (arg1_value == "-level") {
            if (argc < 3) {
                std::cout << "Wrong usage! The argument '-level' requires some value!" << std::endl;
                max_value = -1;
            } else {
                int level = std::stoi(argv[2]);
                switch(level){
                case 1:
                    max_value = 10;
                    break;
                case 2:
                    max_value = 50;
                    break;
                case 3:
                    max_value = 100;
                    break;
                default:
                    std::cout << "Wrong level! The '-level' must be between 1 and 3!" << std::endl;
                    max_value = -1;
                    break;
                }
            }
        } else {
            std::cout << "Wrong usage! Unknown argument: " << arg1_value << std::endl;
            max_value = -1;
        }
    }
    return max_value;
}
