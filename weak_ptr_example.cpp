// Dynamic memory usage example
#include <memory>
#include <iostream>

#include "strategy.hpp"

class WeakSelection {
  public:
    void set(const std::shared_ptr<Unit> &ptr) {
        current_ = ptr;
    }


    void unset() {
        current_.reset();
    }

    void click(int x, int y) {
        if (!current_.expired()) {
            std::shared_ptr<Unit> ptr = current_.lock();
            std::cout << "current_ is not expired\n";
            ptr->move(x, y);
        } else {
            std::cout << "current_ is expired\n";
        }
    }

  private:
    std::weak_ptr<Unit> current_;
};

int main() {
    WeakSelection selection;
    std::shared_ptr<Unit> solder = std::make_shared<Unit>(0, 0);
    selection.set(solder);
    selection.click(100, 100);
    solder.reset();
    selection.click(100, 100);
}
