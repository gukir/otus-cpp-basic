// Dynamic memory usage example
#include <array>
#include <iostream>
#include <thread>
#include <chrono>

#include "strategy.hpp"

void make_unit_and_select(Selection &selection) {
    Unit *solder = new Unit{0, 0};
    selection.set(solder);
}

int main() {
    Selection selection;
    for (;;) {
        make_unit_and_select(selection);
        selection.click(100, 100);
        selection.unset();
        std::this_thread::sleep_for(std::chrono::microseconds(10));
        break;
    }
}
