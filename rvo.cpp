#include <iostream>
#include <string>

//RVO
//NRVO
//copy ellision

// Helper class to trace methods
struct Tracer {
    Tracer() : m_name("empty") {
        std::cout << "default ctor" << std::endl;
    }

    explicit Tracer(const char* x_) : m_name(x_) {
        std::cout << "ctor " << m_name << std::endl;
    }

    Tracer(const Tracer& rhs) { // Why not    : m_name(rhs.m_name)
        std::cout << "copy ctor from " << rhs.m_name << " to " << m_name << std::endl;
        m_name = rhs.m_name;
    }

    ~Tracer() {
        std::cout << "dtor " << m_name << std::endl;
    }

    Tracer& operator=(const Tracer& rhs) {
        std::cout << "copy assign from " << rhs.m_name << " to " << m_name << std::endl;
        m_name = rhs.m_name;
        return *this;
    }
private:
    std::string m_name;
};


// RVO simple
//Tracer makeTracer(void* buff, const char* name) {
//    return Tracer{name};
//}

// int main() {
//
//     std::cout << "example1:" << std::endl;
//
//     // RVO simple example
//     Tracer trace = makeTracer("tracer1");
//     =>
//     Tracer trace("tracer1");
//
//     return 0;
// }


// Expected implementation
// Tracer makeTracer(const char* name) {
//     Tracer temporary(name); // 
//     Tracer result;
//     result = temporary;
//     return result;
// }

// Possible implementation
Tracer makeTracer(const char* name) {
     return Tracer{name};
 }

// int main(int argc, char* argv[]) {
//     Tracer tracer = makeTracer("tracer1"); // original code
    
//     Tracer tracer;
//     makeTracer(&tracer, "tracer1"); // after RVO
// }    



// NRVO simple
Tracer makeTracer2(const char* name) {
    Tracer tracer{name};
    return tracer;
}

// int main(int argc, char* argv[]) {
//
//     std::cout << "example2:" << std::endl;
//
//     // NRVO simple example
//     Tracer tracer2 = makeTracer2("tracer2");
//
//     std::cout << std::endl;
//
//     return 0;
// }



// Expected implementation
// Tracer makeTracer2(const char* name) {
//     Tracer result;
//     Tracer tracer{name};
//     result = tracer;
//     return result;
// }


// RVO medium
Tracer makeTracer3(const char* name, int fake) {
    if (fake % 2) {
        return Tracer{name};
    }
    return Tracer{"other"};
}

//int main(int argc, char* argv[]) {
//
//    std::cout << "example3:" << std::endl;
//
//    // RVO medium
//    Tracer tracer3 = makeTracer3("tracer3", argc);
//
//    std::cout << std::endl;
//
//    return 0;
//}

// NRO medium
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

// int main(int argc, char* argv[]) {
//
//     std::cout << "example4:" << std::endl;
//
//     // NRVO medium
//     Tracer tracer4 = makeTracer4("tracer4", argc);
//
//     return 0;
// }

int main(int argc, char* argv[]) {

    std::cout << "example1:" << std::endl;

    // RVO simple example
    Tracer tracer = makeTracer("tracer1");

    std::cout << std::endl;
    std::cout << "example2:" << std::endl;

    // NRVO simple example
    Tracer tracer2 = makeTracer2("tracer2");

    std::cout << std::endl;
    std::cout << "example3:" << std::endl;

    // RVO medium
    Tracer tracer3 = makeTracer3("tracer3", argc);

    std::cout << std::endl;
    std::cout << "example4:" << std::endl;

    // NRVO medium
    Tracer tracer4 = makeTracer4("tracer4", argc);

    std::cout << "End of the main" << std::endl;

    return 0;
}
