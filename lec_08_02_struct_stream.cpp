#include <fstream>
#include <iostream>
#include <string>

struct Person {
	std::string name;
	std::string surname;
	int age;

};

std::ostream &   operator<< (std::ostream & os, const Person &person) {
	os << person.name << ' ' << person.surname << ', ' << person.age << " years old";
	return os;
}

std::istream &operator>>(std::istream &is, Person &person) {
	is >> person.name >> person.surname >> person.age;
	return is;
}

void func_extract() {

    std::cout << 1 << 2 << "three" << std::endl;

    std::string s = "str_abc";
    int a = 453;
    
    // std::cout << a << s;
    // std::cout.operator<<(a);

    ( operator<<(std::cout, s)).operator<<(a);
    std::cout << std::endl;
    operator<<((std::cout.operator<<(1)).operator<<(2), "three");
}

namespace console {

	void example() {
		std::cout << "*** console::example ***" << std::endl;

		Person person;
		Person person1{"Ivan", "Petrov", 24};
		Person person2{"Petr", "Ivanov", 42};

		std::cout << person1 << std::endl;
		std::cout << person2 << std::endl;
	}

} // console

namespace file {

	void example() {
		std::cout << "*** file::example ***" << std::endl;

		const std::string filename{"testfile.txt"};
		{
			Person person1{"Ivan", "Petrov", 24};
			Person person2{"Petr", "Ivanov", 42};

			std::ofstream file{filename, std::ios_base::binary};
			if (!file.is_open()) {
				std::cerr << "Could not open file for writing: " << filename << std::endl;
				return;
			}

			file << person1;
			file << std::endl;
			file << person2;
		}

		{
			Person person1;
			Person person2;

			std::ifstream file{filename, std::ios_base::binary};
			if (!file.is_open()) {
				std::cerr << "Could not open file for reading: " << filename << std::endl;
				return;
			}

			file >> person1;
			file >> person2;

			std::cout << person1 << std::endl;
			std::cout << person2 << std::endl;
		}
	}

} // file

int main() {

	console::example();
	std::cout << std::endl;
	file::example();

	return 0;
}