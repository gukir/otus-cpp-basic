#include "config.h"
#include "superjob.h"

#include <iostream>

int main(int, char**) {
    std::cout << "Hello from main!" << std::endl;
    superjob::makeSomeSuperJob();
    std::cout << "superjob lib verion:" << superjob::getVersion() << std::endl;

    std::cout << "Main version: " << (PROJECT_VERSION) << std::endl;

    return 0;
}