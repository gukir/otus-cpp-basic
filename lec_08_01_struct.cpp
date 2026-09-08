#include <iostream>
#include <string>

namespace motivation {

	// in     - input parameter
	// out    - output parameter 
	// in/out - input/output parameter

    // 0 or 1 parameter can be returned
	void get_user_info(std::string& name, std::string& surname, int& age) {

		std::cout << "Hello!" << std::endl;
		
		std::cout << "Enter your name:" << std::endl;
		std::cin >> name;

		std::cout << "Enter your surname:" << std::endl; 
		std::cin >> surname;

		std::cout << "Enter your age:" << std::endl;
		std::cin >> age;
	}

	void example() {

		std::string name;
		std::string surname;
		int age;

		get_user_info(name, surname, age);

		if (age < 16) {
			std::cout << "Access denied!" << std::endl;
		}
		else if (age < 30) {
			std::cout << "Hello, " << name << std::endl;
		}
		else {
			std::cout << "Hello, " << name << " " << surname << std::endl;
		}
	}

} // motivation


namespace structures {

    // Combine related data in a stand alone abstraction
	struct Person {

		std::string name;
		std::string surname = "Ivanov";
		int age;
	};
	
	Person get_user_info() {

		Person   person;

		std::cout << "Hello!" << std::endl;
		
		std::cout << "Enter your name:" << std::endl;
		std::cin >> person.name;

		std::cout << "Enter your surname:" << std::endl; 
		std::cin >> person.surname;

		std::cout << "Enter your age:" << std::endl;
		std::cin >> person.age;

		return person;
	}

	void example() {

		Person person = get_user_info();

		if (person.age < 16) {
			std::cout << "Access denied!" << std::endl;
		}
		else if (person.age < 30) {
			std::cout << "Hello, " << person.name << std::endl;
		}
		else {
			std::cout << "Hello, " << person.name << " " << person.surname << std::endl;
		}
	}
} // namespace structures

int main() {

	motivation::example();
	structures::example();

	return 0;
}
