#include <cstddef>
#include <iostream>

namespace lec11
{

template <std::size_t n>
std::size_t factorial() 
{
    return n * factorial<n - 1>();
}

template <>
std::size_t factorial<0>()
{
    return 1;
}

}

int main()
{
    std::cout << "factorial " << lec11::factorial<5>() << std::endl;

    return 0;
}
