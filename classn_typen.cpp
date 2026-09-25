#include <iostream>

template<typename T>
struct A
{
    typedef T _my_type;

    _my_type variable;
};

template<typename T>
struct B
{
    A::_my_type _stolen_variable;
};




template<typename T>
void type_function(T* t_ptr)
{
    std::cout << t_ptr << std::endl;
}


template<class C>
void class_function(C* c_ptr)
{
    std::cout << c_ptr << std::endl;
}

int main()
{
    
    return 0;
}