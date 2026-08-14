#include <iostream>

namespace basics {

    // monday, tuesday, wednesday, thursday, friday, saturday, sunday
    std::string int_to_day(int number) {
        std::string result{};

        // В switch допустипо использовать только выражения
        // целочисленного типа (int, long, и т.д.) или enum (и enum class)
        switch (number) {
        case 1:
            result = "Monday";
            break;
        case 2:
            result = "Tuesday";
            break;
        case 3:
            result = "Wednesday";
            break;
        case 4:
            result = "Thursday";
            break;
        case 5:
            result = "Friday";
            break;
        case 6:
            result = "Saturday";
            break;
        case 7:
            result = "Sunday";
            break;
        default:
            result = "Invalid input";
            break;
        }
        return result;
    }

    void example() {
        int day{0};
        std::cout << "[basics::example] Enter the day number [1..7]: ";
        std::cin >> day;
        std::cout << "The result is: " << basics::int_to_day(day) << std::endl;
    }

} // namespace basics

namespace enums {

    enum class Direction {
        Left,
        Right,
        Up,
        Down,
        Invalid
    };

    Direction int_to_direction(int direction) {
        switch (direction) {
        case 0:
            return Direction::Left;
        case 1:
            return Direction::Up;
        case 2:
            return Direction::Right;
        case 3:
            return Direction::Down;
        default:
            return Direction::Invalid;
        }
    }

    std::string direction_to_string(Direction direction) {
        switch (direction) {
        case Direction::Left:
            return "Left";
        case Direction::Right:
            return "Right";
        case Direction::Up:
            return "Up";
        case Direction::Down:
            return "Down";
        case Direction::Invalid:
            return "Invalid";
        default:
            return "Unknown";
        }
    }

    void example() {

        std::cout << "[enums::example] Hello to the \"Big jornay\" app!" << std::endl;
        while (true) {
            int direction{0};
            std::cout << "Enter the next direction to move [0 - Left, 1 - Up, 2 - Right, 3 - Down]: ";
            std::cin >> direction;

            std::string text = direction_to_string( int_to_direction(direction) );
            std::cout << "Greate! You moved to the " << text << std::endl;
        }
    }

} // namespace enums

int main() {

    basics::example();

    enums::example();

    return 0;
}