#include <iostream>

struct Person {
	std::string name;
	std::string surname;
	int age;
};

namespace without_operators {

	void example() {
#if 0
		Person p1{"Ivan", "Petrov", 24};
		Person p2{"Petr", "Ivanov", 42};

		std::cout << std::boolalpha;

		// Will not compile:
		// no match for 'operator<' (operand types are 'Person' and 'Person')
	
		std::cout << "p1  < p2 = " << (p1 <  p2) << std::endl;
		std::cout << "p1 == p2 = " << (p1 == p2) << std::endl;
		std::cout << "p1 <= p2 = " << (p1 <= p2) << std::endl;
		std::cout << "p1  > p2 = " << (p1 >  p2) << std::endl;
		std::cout << "p1 >= p2 = " << (p1 >= p2) << std::endl;
#endif
	}

} // without_operators

// We can overload 	any of the following operators:
//     + - * / % ^ & | ~ ! = < >
//     += -= *= /= %= ^= &= |=
//     << >> >>= <<=
//     == != <= >= 
//     && || ++ --
//     , ->* -> ( ) [ ]


// lhs < rhs
// lhs - left  hand side
// rhs - right hand side
bool operator< (const Person& lhs, const Person& rhs) {

	if (lhs.age < rhs.age)       return true;
	else if (lhs.age > rhs.age)  return false;

	if (lhs.name < rhs.name)     return true;
	else if (lhs.age > rhs.age)  return false;

	if (lhs.surname < rhs.surname) return true;

	return false;
}

bool operator> (const Person& lhs, const Person& rhs) {
	return rhs < lhs;
}

bool operator== (const Person& lhs, const Person& rhs) {
	return !(lhs < rhs) && !(rhs < lhs);
}

bool operator<= (const Person& lhs, const Person& rhs) {
	return (lhs < rhs) || (lhs == rhs);
}

bool operator>= (const Person& lhs, const Person& rhs) {
	return (lhs > rhs) || (lhs == rhs);
}

namespace with_operators {

	void example() {
		Person p1{"Ivan", "Petrov", 24};
		Person p2{"Petr", "Ivanov", 42};

		// Ask cout to print boolean values as true/false instead of 1/0
		std::cout << std::boolalpha;

		std::cout << "p1 < p2 = " << (p1 < p2) << std::endl;
		std::cout << "p1 == p2 = " << (p1 == p2) << std::endl;
		std::cout << "p1 <= p2 = " << (p1 <= p2) << std::endl;
		std::cout << "p1 > p2 = " << (p1 > p2) << std::endl;
		std::cout << "p1 >= p2 = " << (p1 >= p2) << std::endl;
	}

} // with_operators

// Outside the class

struct Point2D
{
	float x;
	float y;

	bool operator==(const Point2D& ) const;
	void info() const;
	// void info();
};

bool Point2D::operator==(const Point2D& p) const
{
	return this->x < p.x;
}

void example() {
	const Point2D p{1.f, 2.f};
	p.info();
}

void Point2D::info() const {
	std::cout << "Super point " << std::endl;
}

// Const correctness
void drawPoint(const Point2D& p1) {

	//p1.info();
	std::cout << " (" << p1.x << "," << p1.y << ") " << std::endl;
}

int main() {

	without_operators::example();
	with_operators::example();

	return 0;
}