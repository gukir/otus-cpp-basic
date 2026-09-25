#include <iostream>

template<typename T>
T Function(char*c)
{
    std::cout << "GENERAL TEMPLATE!\n";
    return (T)(*c);
}

template<>
int Function<int>(char* c)
{
    std::cout << "SPECIALIZATION\n";
    return (int)(*c);
}


int main()
{
    char a = '%';
    int r = Function<int>(&a);
    return 0;
}