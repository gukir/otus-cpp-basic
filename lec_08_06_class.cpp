#include <iostream>
#include <cmath>

// OOP
// Object oriented programming:
// - encapsulation 
// - inheritance 
// - polymorphism 
// - abstraction

namespace explicitly {

	class Complex {
	public:
		Complex() {}
		Complex(double real, double img):
		m_real(real), m_img(img) {

		}
		// Also possible:
		// Complex(double real, double img) {
		// 	m_real = real;
		// 	m_img = img;
		// }

		double abs() const {
			return std::sqrt(m_real * m_real + m_img * m_img);
		}

		double angle() const {
			return std::atan2(m_img, m_real);
		}

	private:
		double m_real = 23;
		double m_img = 34;
	};

	void func() {
		Complex complex{13.0, 42.0};
		
		// Complex::abs(&complex);
		complex.abs(); // 	
		
		complex.angle();
	}

} // namespace explicitly

namespace separated {

	// could be in the header
	class Complex {
	public:
		Complex();
		Complex(double real, double im);
		~Complex();

		double abs() const;
		double angle() const;

		void set_real(double real);
		void set_img(double img);

	private:
		double m_real;
		double m_img;
	};

	void func() {
		{
			Complex complex; // Complex()
		} // 

		Complex* ptr = new Complex{42.0, 13.0};
		delete ptr; // Complex::~Complex

		const Complex complex;

		Complex complex2{42.0, 13.0}; // Complex(double real, double im)
		Complex complex3(42.0, 13.0); // Complex(double real, double im)
	} // 

	// could be in the .cpp file
	Complex::Complex() {
		std::cout << "Default constructor" << std::endl;
	}

	Complex::Complex(double real, double img)
		: m_real{real}, m_img{img} {
		std::cout << "constructor with arguments" << std::endl;
	}

	Complex::~Complex() {
		std::cout << "destructor" << std::endl;
	}

	double Complex::abs() const {
		return std::sqrt(m_real * m_real + m_img * m_img);
	}

	double Complex::angle() const {
		return std::atan2(m_img, m_real);
	}

	void Complex::set_real(double real) {
		m_real = real;
	}

	void Complex::set_img(double img) {
		m_img = img;
	}

} // namespace separated


int main() {

	return 0;
}