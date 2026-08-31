#include <iostream>
#include "argument.h"
#include "check_value.h"
#include "high_scores.h"
#include "random_value.h"

int main(int argc, char** argv) {

    int max_value;
    max_value = argument(argc, argv);

    if (max_value < 0) {
        std::cout << "Error! The program is finished." << std::endl;
    } else if (max_value == 0) {
        high_scores(max_value);
    } else {
        std::cout << "Hi! Enter your name, please:" << std::endl;
        std::string user_name;
        std::cin >> user_name;
        high_scores(check_value(random_value(max_value)), user_name);
    }

	return 0;
}
