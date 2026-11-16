#include <cstring>
#include <exception>
#include <new>

class Person {
public:
    Person(const char* firstname, const char* lastname) {
        try {
            firstname_ = new char[std::strlen(firstname) + 1];
            std::strcpy(firstname_, firstname);
            lastname_ = new char[std::strlen(lastname) + 1];
            std::strcpy(lastname_, lastname);
        } catch (const std::bad_alloc &) {
            delete firstname_;
            throw;
        }
    }

    ~Person() {
        delete firstname_;
        delete lastname_;
    }
private:
    char *firstname_;
    char *lastname_;
};


int main() {
    try {
        Person john{"John", "Smith"};
    } catch (...) {

    }
}