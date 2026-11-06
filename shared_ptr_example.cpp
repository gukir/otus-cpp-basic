// Dynamic memory usage example
#include <memory>

#include "strategy.hpp"

class SharedSelection {
  public:
    void set(const std::shared_ptr<Unit> &ptr) {
        current_ = ptr;
    }

    void set(std::shared_ptr<Unit> &&ptr) {
        current_ = std::move(ptr);
    }

    void unset() {
        current_.reset();
    }

    void click(int x, int y) {
        if (current_) {
            current_->move(x, y);
        }
    }

  private:
    std::shared_ptr<Unit> current_;
};

int main() {
    SharedSelection selection;
    std::shared_ptr<Unit> solder = std::make_shared<Unit>(0, 0);
    selection.set(solder);
    solder.reset();
    selection.click(100, 100);
}
