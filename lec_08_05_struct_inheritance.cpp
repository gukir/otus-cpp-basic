#include <iostream>

// Rule
// SemiColonRule -> Rule

// Building
// School -> Building

// Food
// FastFood -> Food

struct Person2 {
    int age;
    
	struct iterator {
        int time_gob;
    };
};

struct Person {
	std::string surname;
	std::string name;
	int age;
};

enum class Post {
	manager,
	developer,
	QA
};

// Employee is also Person.
struct Employee : public Person {
	// std::string name;		// This field comes from Person
	// std::string surname;		// This field comes from Person
	// int age;					// This field comes from Person
	Post post;					// This field is new
};

namespace sizing {

	void example() {
		std::cout << "*** sizing::example ***" << std::endl;

		Person person{
			"Name",
			"Last name",
			42
		};

		Employee employee{
			"Name",
			"Last name",
			24,
			Post::developer
		};
		employee.name = "New name";

		std::cout << "sizeof(person) = " << sizeof(person) << std::endl;
		std::cout << "sizeof(employee) = " << sizeof(employee) << std::endl;
	}
}

bool operator<(const Person &lhs, const Person &rhs) {
	if (lhs.age < rhs.age)
		return true;
	else if (lhs.age > rhs.age)
		return false;

	if (lhs.name < rhs.name)
		return true;
	else if (lhs.age > rhs.age)
		return false;

	if (lhs.surname < rhs.surname)
		return true;
	return false;
}

bool operator>(const Person &lhs, const Person &rhs) {
	return rhs < lhs;
}

bool operator==(const Person &lhs, const Person &rhs) {
	return !(lhs < rhs) && !(rhs < lhs);
}

bool operator<=(const Person &lhs, const Person &rhs) {
	return (lhs < rhs) || (lhs == rhs);
}

bool operator>=(const Person &lhs, const Person &rhs) {
	return (lhs > rhs) || (lhs == rhs);
}

std::ostream &operator<<(std::ostream &os, const Person &person) {
	os << person.name << ' ' << person.surname << ' ' << person.age;
	return os;
}

namespace operators {

	void example() {
		std::cout << "*** operators::example ***" << std::endl;

		Person person1{
			"Name",
			"Last name",
			42};

		Person person2{
			"Name",
			"Last name",
			24};

		// It works because we've made operators overloading for Person
		std::cout << "(person1 == person2) = " << (person1 == person2) << std::endl;

		Employee employee1{
			"Name",
			"Last name",
			24,
			Post::developer
		};
		
		Employee employee2{
			"Name",
			"Last name",
			24,
			Post::manager
		};

		// It works also??
		std::cout << "(employee1 == employee2) = " << (employee1 == employee2) << std::endl;
		// operator==(const Employee& lhs, const Employee& rhs);
		// operator==(const Person& lhs, const Person& rhs);
	}
} // namespace operators

std::ostream &operator<<(std::ostream &os, const Employee &employee) {
	// operator<<(std::ostream&, const Person&)
	os << static_cast<const Person &>(employee);
	os << ' ' << static_cast<int>(employee.post);
	return os;
}

namespace slicing {

	void some_function(const Person &person) {
		std::cout << "Hello from function with Person argument!" << std::endl;
		std::cout << person << std::endl;
	}

	void some_other_function(const Employee &employee) {
		std::cout << "Hello from function with Employee argument!" << std::endl;
		std::cout << employee << std::endl;
	}

	void example() {
		std::cout << "*** slicing::example ***" << std::endl;

		Person person{
			"Person",
			"Person",
			42};
		// It works. Good.
		some_function(person);
		// It does not work - Person IS NOT Employee
		// some_other_function(person);

		Employee employee{
			"Employee",
			"Employee",
			24,
			Post::manager};
		// It works. Good.
		some_other_function(employee);
		// It works also! Peson IS Employee
		some_function(employee);
	}

} // namespace slicing

int main() {
	sizing::example();
	operators::example();
	slicing::example();

	return 0;
}