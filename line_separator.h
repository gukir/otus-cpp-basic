#pragma once
#include <iostream>
#include <string_view>

struct LineSeparator {
    static void out(const std::string_view& msg) {
        std::cout << "\n---------------------------------";
        std::cout << msg;
        std::cout << "---------------------------------" << std::endl;
        ;
    }
};