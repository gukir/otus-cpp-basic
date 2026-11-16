#include <iostream>
#include <string>
#include <vector>

// Move medium
void someStrangeFunction() {
    std::string name{"Vasia"};

    std::string name2 = std::move(name);

    std::cout << name << std::endl;
}

// Possible implementation
template <typename T>
typename std::remove_reference<T>::type&& move(T&& arg) {
    return static_cast<typename std::remove_reference<T>::type&&>(arg);
}




// Move basic
void handleBigObjectFunc(std::string& bigString) {
    // just a reference here - it is not an "temporary" or "moved" object
}


void handleBigObjectFunc(std::string&& bigString) {
    // r-value reference here - it is a "temporary" or "moved" object
}

// Helper class to trace methods (with move ctor and operator= now!)
struct Tracer {
    Tracer() : m_name{"empty"} {

    }

    explicit Tracer(const char *x_) : m_name(x_) {
        std::cout << "ctor " << m_name << std::endl;
    }

    Tracer(const Tracer &rhs) : m_name(rhs.m_name) {
        std::cout << "copy ctor from " << rhs.m_name << " to " << m_name << std::endl;
    }

    Tracer(Tracer &&rhs) noexcept {
        std::cout << "move ctor from " << rhs.m_name << " to " << m_name << std::endl;
        m_name.swap(rhs.m_name);
    }

    ~Tracer() {
        std::cout << "dtor " << m_name << std::endl;
    }

    Tracer &operator=(const Tracer &rhs) {
        std::cout << "copy assign from " << rhs.m_name << " to " << m_name << std::endl;
        return *this;
    }

    Tracer &operator=(Tracer &&rhs) noexcept {
        std::cout << "move assign from " << rhs.m_name << " to " << m_name << std::endl;
        m_name.swap(rhs.m_name);
        return *this;
    }
private:
    std::string m_name;
};


Tracer makeTracer4(const char* name, int fake) {
    if (fake % 2) {
        Tracer result1{name};
        return result1;
    }
    else {
        Tracer result2{"other"};
        return result2;
    }
}


int main(int argc, char* arg[]) {
    // Move medium
    someStrangeFunction();


    // Move basic
    std::string bigString{"very very big string"}; // 10 GB
    
    handleBigObjectFunc(bigString);
    
    handleBigObjectFunc(std::move(bigString));

    Tracer bigTracer{"bigTracer1"}; // 10 GB here
    Tracer otherTracer{"otherTracer"};

    otherTracer = bigTracer; // 20 GB here

    otherTracer = std::move(bigTracer); // maybe only 10 GB here

    std::cout<<"!!!!!"<<std::endl;
    Tracer moveTracer = makeTracer4("moveTracer", argc);

    std::cout << "End of the main" << std::endl;
    
    std::vector<Tracer> vec1;
    //vec1.reserve(10);
    //{Tracer{"123"},Tracer{"456"}};
    vec1.emplace_back("123");
    vec1.emplace_back("456");
//    vec1.push_back(Tracer("123"));
//    vec1.push_back(Tracer("456"));

    return 0;
}
