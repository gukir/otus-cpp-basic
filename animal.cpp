#include <iostream>
#include <string>
#include <vector>

namespace without_virtual {

	// Abstraction for all cat-like animals: cats, tigers, lions, ets.
	class Felidae {
	public:
		Felidae(const std::string &name)
			: m_name{name} {
			std::cout << "Felidae constructor" << std::endl;
		}

		~Felidae() {
			std::cout << "Felidae destructor" << std::endl;
		}

		void speak() const {
			// Hm...
			// It is not a some concrete animal - it is an abstraction.
			// How does the abstraction speak? :)
			std::cout << "Hm... What should we write here?" << std::endl;
		}

		void call() const {
			// Ok - We can call ANY cat-like by name.
			std::cout << m_name << ", come here!" << std::endl;
		}

		std::string get_name() const { return m_name; }

	private:
		std::string m_name;
	};

	// The concrete animal - cat
	class Cat : public Felidae {
	public:
		Cat(const std::string &name, const std::string &breed)
			: Felidae{name}, m_breed{breed} {

			Felidae::speak();
			std::cout << "Cat constructor" << std::endl;
		}

		~Cat() {
			std::cout << "Cat destructor" << std::endl;
		}

		void speak() const {
			// Easy! Cats say "meow".
			std::cout << "Meow, meow, meow!" << std::endl;
		}

		void call() const {
			// Ok - We can call cat by it's name.
			std::cout << get_name() << ", kitty, kitty, kitty, come here!" << std::endl;
		}

	private:
		std::string m_breed;
	};

	// The concrete animal - lion
	class Lion : public Felidae {
	public:
		Lion(const std::string &name, int age)
			: Felidae{name}, m_age{age} {
			std::cout << "Lion constructor" << std::endl;
		}

		~Lion() {
			std::cout << "Lion destructor" << std::endl;
		}

		void speak() const {
			// Not so easy, but also known.
			std::cout << "Grrrrrrr!" << std::endl;
		}

		void call() const {
			// It is not a very good idea to call a lion...
			std::cout << get_name() << ", don't eat me, please!" << std::endl;
		}

	private:
		int m_age;
	};

	void work_with(const Felidae &felidae) {
		std::cout << "-- work_with felidae::speak()" << std::endl;
		felidae.speak();

		std::cout << "-- work_with felidae::call()" << std::endl;
		felidae.call();
	}

	void example() {
		std::cout << "*** without_virtual::example() ***" << std::endl;

		// Scope here just to see the destructors in good order
		{
			// Create an abstract cat-like animal? Hm...
			std::cout << "-- Felidae creation:" << std::endl;
			Felidae felidae{"Sparky"};

			std::cout << "-- Felidae::speak():" << std::endl;
			felidae.speak();

			std::cout << "-- Felidae::call():" << std::endl;
			felidae.call();

			// Call a function with reference to the felidae:
			work_with(felidae);
		}
		// The output from this scope:

		// -- Felidae creation:
		// Felidae constructor
		// -- Felidae::speak():
		// Hm... What should I write here?
		// -- Felidae::call():
		// Sparky, come here!
		// -- work_with felidae::speak()
		// Hm... What should I write here?
		// -- work_with felidae::call()
		// Sparky, come here!
		// Felidae destructor

		std::cout << std::endl;

		// Scope here just to see the destructors in good order
		{
			std::cout << "-- Cat creation:" << std::endl;
			Cat cat{"Casper", "Persian"};

			std::cout << "-- Cat::speak():" << std::endl;
			cat.speak();

			std::cout << "-- Cat::call():" << std::endl;
			cat.call();

			// Call a function with reference to the cat:
			work_with(cat);
		}
		// The output from this scope:

		// -- Cat creation:
		// Felidae constructor
		// Cat constructor
		// -- Cat::speak():
		// Meow, meow, meow!
		// -- Cat::call():
		// Casper, kitty, kitty, kitty, come here!
		// 	-- work_with felidae::speak()
		// 	Hm... What should I write here?
		// 	-- work_with felidae::call()
		// 	Casper, come here!
		// Cat destructor
		// Felidae destructor

		std::cout << std::endl;

		// Scope here just to see the destructors in good order
		{
			std::cout << "-- Lion creation:" << std::endl;
			Lion lion{"Simba", 10};

			std::cout << "-- Lion::speak():" << std::endl;
			lion.speak();

			std::cout << "-- Lion::call():" << std::endl;
			lion.call();

			// Call a function with reference to the lion:
			work_with(lion);
		}
		// The output from this scope:

		// -- Lion creation:
		// Felidae constructor
		// Lion constructor
		// -- Lion::speak():
		// Grrrrrrr!
		// -- Lion::call():
		// Simba, don't eat me, please!
		// -- work_with felidae::speak()
		// Hm... What should I write here?
		// -- work_with felidae::call()
		// Simba, come here!
		// Lion destructor
		// Felidae destructor

		std::cout << std::endl;
	}

	void example_collection() {
		std::cout << "*** without_virtual::example_collection ***" << std::endl;

		// We want a collection on animals
		std::vector<Felidae *> animals = {
			new Cat{"Casper", "Persian"},
			new Lion{"Simba", 10}};
		// Output:
		// Felidae constructor
		// Cat constructor
		// Felidae constructor
		// Lion constructor

		// Looks good

		// And than we want to work with animals like with an abstraction:
		for (auto animal : animals) {
			animal->speak();
		}
		// Output:
		// Hm... What should I write here?
		// Hm... What should I write here?

		// It is not what we want :(

		// Clear memory after creation objects by new
		for (auto animal : animals) {
			delete animal;
		}
		// Output:
		// Felidae destructor
		// Felidae destructor

		// It is not what we want :(
	}

} // namespace without_virtual

namespace with_virtual {

	// Abstraction for all cat-like animals: cats, tigers, lions, ets.
	class Felidae {
	public:
		Felidae(const std::string &name)
			: m_name{name} {
			std::cout << "Felidae constructor" << std::endl;
		}

		virtual ~Felidae() {
			std::cout << "Felidae destructor" << std::endl;
		}

		// Pure-virtual method - because we can't implement in for the
		// abstract cat-like animal
		virtual void speak() const = 0;

		// virtual method - we can make a some default implementation
		// for all cat-like animals
		virtual void call() const {
			// Ok - I can call ANY cat-like by name.
			std::cout << m_name << ", come here!" << std::endl;
		}

		// Non-virual method. We don't want to change a behavior in the
		// derived classes.
		std::string get_name() const { return m_name; }

	private:
		std::string m_name;
	};

	void example_pure_virtual() {
		// Compile time error here:
		// Felidae felidae{"Unknown"};

		// animal.cpp: In function 'void example_pure_virtual()':
		// animal.cpp: error: cannot declare variable 'felidae' to be of abstract type 'Felidae'
		//       |  Felidae felidae{"Unknown"};
		//       |          ^~~~~~~
		// animal.cpp: note:   because the following virtual functions are pure within 'Felidae':
		//       | class Felidae {
		//       |       ^~~~~~~
		// animal.cpp: note:     'virtual void Felidae::speak() const'
		//       |  virtual void speak() const = 0;
		//       |               ^~~~~

		// We can't create an object of the class if it has any pure-virtual methods!
		// It means than we don't need an "abstract" objects - we need only objects of the
		// derived classes.
	}

	// The concrete animal - cat
	class Cat : public Felidae {
	public:
		Cat(const std::string &name, const std::string &breed)
			: Felidae{name}, m_breed{breed} {
			std::cout << "Cat constructor" << std::endl;
		}

		virtual ~Cat() {
			std::cout << "Cat destructor" << std::endl;
		}

		virtual void speak() const override {
			// Easy! Cats say "meow".
			std::cout << "Meow, meow, meow!" << std::endl;
		}

		virtual void call() const override {
			// Ok - We can call cat by it's name.
			std::cout << get_name() << ", kitty, kitty, kitty, come here!" << std::endl;
		}

	private:
		std::string m_breed;
	};

	// The concrete animal - lion
	class Lion : public Felidae {
	public:
		Lion(const std::string &name, int age)
			: Felidae{name}, m_age{age} {
			std::cout << "Lion constructor" << std::endl;
		}

		virtual ~Lion() {
			std::cout << "Lion destructor" << std::endl;
		}

		virtual void speak() const override {
			// Not so easy, but also known.
			std::cout << "Grrrrrrr!" << std::endl;
		}

		virtual void call() const override {
			// It is not a very good idea to call a lion...
			std::cout << get_name() << ", don't eat me, please!" << std::endl;
		}

	private:
		int m_age;
	};

	void work_with(const Felidae &felidae) {
		std::cout << "-- work_with felidae::speak()" << std::endl;
		felidae.speak();

		std::cout << "-- work_with felidae::call()" << std::endl;
		felidae.call();
	}

	void example() {
		std::cout << "*** with_virtual::example() ***" << std::endl;

		// Will not compile. See example example_pure_virtual for details.
		// {
		// 	// Create an abstract cat-like animal? Hm...
		// 	std::cout << "-- Felidae creation:" << std::endl;
		// 	Felidae felidae{"Sparky"};

		// 	std::cout << "-- Felidae::speak():" << std::endl;
		// 	felidae.speak();

		// 	std::cout << "-- Felidae::call():" << std::endl;
		// 	felidae.call();

		// 	// Call a function with reference to the felidae:
		// 	work_with(felidae);
		// }
		// The output from this scope:

		std::cout << std::endl;

		// Scope here just to see the destructors in good order
		{
			std::cout << "-- Cat creation:" << std::endl;
			Cat cat{"Casper", "Persian"};

			std::cout << "-- Cat::speak():" << std::endl;
			cat.speak(); // Cat::speak()

			std::cout << "-- Cat::call():" << std::endl;
			cat.call();

			// Call a function with reference to the cat:
			work_with(cat);
		}
		// The output from this scope:

		// -- Cat creation:
		// Felidae constructor
		// Cat constructor
		// -- Cat::speak():
		// Meow, meow, meow!
		// -- Cat::call():
		// Casper, kitty, kitty, kitty, come here!
		// -- work_with felidae::speak()
		// Meow, meow, meow!
		// -- work_with felidae::call()
		// Casper, kitty, kitty, kitty, come here!
		// Cat destructor
		// Felidae destructor

		std::cout << std::endl;

		// Scope here just to see the destructors in good order
		{
			std::cout << "-- Lion creation:" << std::endl;
			Lion lion{"Simba", 10};

			std::cout << "-- Lion::speak():" << std::endl;
			lion.speak();

			std::cout << "-- Lion::call():" << std::endl;
			lion.call();

			// Call a function with reference to the lion:
			work_with(lion);
		}
		// The output from this scope:

		// -- Lion creation:
		// Felidae constructor
		// Lion constructor
		// -- Lion::speak():
		// Grrrrrrr!
		// -- Lion::call():
		// Simba, don't eat me, please!
		// -- work_with felidae::speak()
		// Grrrrrrr!
		// -- work_with felidae::call()
		// Simba, don't eat me, please!
		// Lion destructor
		// Felidae destructor

		std::cout << std::endl;
	}

	void
	example_collection() {
		std::cout << "*** with_virtual::example_collection ***" << std::endl;

		// We want a collection on animals
		std::vector<Felidae *> animals = {
			new Cat{"Casper", "Persian"},
			new Lion{"Simba", 10}};

		// operator<<(std::cout, 42);

		std::cout.operator<<(42);

		// a.operator<<(b)
		// operator<<(a, b)

		// Output:
		// Felidae constructor
		// Cat constructor
		// Felidae constructor
		// Lion constructor

		// Looks good

		// And than we want to work with animals like with an abstraction:
		for (auto animal : animals) {
			animal->speak();
		}
		// Output:
		// Meow, meow, meow!
		// Grrrrrrr!

		// Looks good!

		// Clear memory after creation objects by new
		for (auto animal : animals) {
			delete animal;
		}
		// Output:
		// Cat destructor
		// Felidae destructor
		// Lion destructor
		// Felidae destructor

		// Looks good!
	}

} // namespace with_virtual

int main() {

	without_virtual::example();
	std::cout << std::endl;

	without_virtual::example_collection();
	std::cout << std::endl;

	with_virtual::example_pure_virtual();
	std::cout << std::endl;

	with_virtual::example();
	std::cout << std::endl;

	with_virtual::example_collection();
	std::cout << std::endl;

	return 0;
}