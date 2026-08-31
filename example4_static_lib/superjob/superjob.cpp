#include "superjob.h"
#include "config.h"

#include <iostream>

namespace superjob {

    int makeSomeSuperJob() {
        std::cout << "Hello from superjob lib!" << std::endl;
        return 42;
    }

    int getVersion() {
        return (PROJECT_VERSION);
    }

}