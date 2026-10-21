#include "../my_list.h"

// Создаем класс фикстуры, наследуемый от ::testing::Test
class ListF : public ::testing::Test {
protected:
    // SetUp вызывается перед каждым тестом (TEST_F)
    void SetUp() override {
        // Наполняем список значениями
        for(int i = 0; i < 5; i++){
          l1.push_back(i);
        }
    }

    // TearDown вызывается после каждого теста (опционально, если нужна очистка)
    void TearDown() override {
        // В данном случае память очистится автоматически при уничтожении объекта (проверим для надежности valgrind'ом)
    }

    // Общие данные, доступные во всех тестах, использующих эту фикстуру
    MyVector<int> l1, l2;
};