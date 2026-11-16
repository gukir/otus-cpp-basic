#include <iostream>
#include <string>
#include <vector>


#define UNUSED(variable) (void)variable

// void testFunc(int i) {
//     std::cout << "int" << std::endl;
// }

void testFunc(int& i) {
    std::cout << "int&" << std::endl;
}

void testFunc(int&& i) {
    std::cout << "int&&" << std::endl;
}


template<typename T>
void testUnirefFunc(T&& param) {
    // param
}


int main() {

    int i = 42;

    auto ai = i; // of course, int
    testFunc(ai);

    auto& ai_ref = i; // int&
    testFunc(ai_ref);

    auto&& ai_rvalue = i; // still int
    testFunc(ai_rvalue);

    testFunc(std::move(i));

    auto&& ai_move = std::move(i);
    
    testFunc(ai_move);
    
    testFunc(std::forward<int>(ai_move));
    return 0;
}
