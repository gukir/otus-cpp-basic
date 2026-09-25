#include <iostream>

	// operators:
	// + - * / % ^ & | ~ ! = < > += -= *= /= %= ^= &= |= 
	// << >> >>= <<= == != <= >= 
	// <=> (since C++20) 
	// && || ++ -- , ->* -> ( ) [ ]

	// Restrictions
	// The operators 
	//     :: (scope resolution), 
	//      . (member access), 
	//     .* (member access through pointer to member), 
	//     ?: (ternary conditional) 
	// cannot be overloaded.

	// New operators such as **, <>, or &| cannot be created.
	// It is not possible to change the precedence, grouping, or number of operands of operators.
	// The overload of operator -> must either return a raw pointer, 
	// or return an object (by reference or by value) for which operator -> is in turn overloaded.
	// The overloads of operators && and || lose short-circuit evaluation.


struct MySuperInteger {
public:
    MySuperInteger(int v) : m_value{v} {}

    MySuperInteger operator+(const MySuperInteger& rhs) { // right-hand-side
        return MySuperInteger{m_value + rhs.m_value};
    }

    MySuperInteger& operator=(const MySuperInteger& rhs) {
        m_value += rhs.m_value;
        return *this;
    }
private:
    // может быть как в private, так и в public, так и в protected секциях - это ни на что не влияет
    friend MySuperInteger operator+(int lhs, const MySuperInteger& rhs);
    friend std::ostream& operator<<(std::ostream& os, const MySuperInteger& rhs);

    int m_value;
};


MySuperInteger operator+(int lhs, const MySuperInteger& rhs) {
    return MySuperInteger{lhs + rhs.m_value}; // rhs.m_value доступно только благодаря friend
}

std::ostream& operator<<(std::ostream& os, const MySuperInteger& rhs) {
    os << rhs.m_value;
    return os;
}


void test() {
    MySuperInteger v1{42};
    MySuperInteger v2{24};

    std::cout << v1 << " + " << v2 << " = " << v1 + v2 << std::endl;

    std::cout << v1 << " + " << 56 << " = " << v1 + 56 << std::endl;

    std::cout << 65 << " + " << v1 << " = " << 65 + v1 << std::endl;
}






int main() {
    test();
    return 0;
}