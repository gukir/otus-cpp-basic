#include <iostream>

template<typename T>
constexpr T pi = T(3.1415926535897932385L);

template<typename T>
T Function(T arg)
{
    //float * double == result_type?
    // 
    return pi<T> * arg;


}

int main()
{

    double a = 2.222222;
    float b = 3.3333333;
    int c = 4;


    std::cout << Function(a) << std::endl;
    std::cout << Function(b) << std::endl;
    std::cout << Function(c) << std::endl;
    return 0;
}