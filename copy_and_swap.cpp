#include <string>

class Person {
public:
    Person(const char* firstname, const char* lastname)
        : firstname_{firstname}
        , lastname_{lastname} {
    }

    Person(const Person &other)
        : firstname_{other.firstname_}
        , lastname_{other.lastname_}
    {}

    Person &operator=(const Person &other) {
        // Copy and swap idiom        
        Person tmp{other};
        //swap(tmp);
        return *this;
    }

    // Implement swap method
    void swap(Person &other) noexcept;

private:
    std::string firstname_;
    std::string lastname_;
};

int main() {
    
}