#include <iostream>
#include "my_vector.h"

int main() {
    using Container = MyVector<int>;
	// создание объекта контейнера для хранения объектов типа int
    Container container;
	// добавление в контейнер десяти элементов (0, 1 … 9)
    for(int i = 0; i < 10; i++){
        container.push_back(i);
    }
	// вывод содержимого контейнера на экран
	// (ожидаемый результат: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9)
    std::cout << container << std::endl;
	// вывод размера контейнера на экран
	// (ожидаемый результат: 10)
    std::cout << container.size() << std::endl;
	// удаление третьего (по счёту), пятого и седьмого элементов
    std::size_t for_del[] = {2, 4, 6};
    container.erase(for_del, static_cast<std::size_t>(sizeof(for_del) / sizeof(for_del[0])));
	// вывод содержимого контейнера на экран
	// (ожидаемый результат: 0, 1, 3, 5, 7, 8, 9)
    std::cout << container << std::endl;
	// добавление элемента 10 в начало контейнера
    container.push_front(10);
	// вывод содержимого контейнера на экран
	// (ожидаемый результат: 10, 0, 1, 3, 5, 7, 8, 9)
    std::cout << container << std::endl;
	// добавление элемента 20 в середину контейнера
    container.insert(static_cast<std::size_t>(container.size() / 2), 20);
	// вывод содержимого контейнера на экран
	// (ожидаемый результат: 10, 0, 1, 3, 20, 5, 7, 8, 9)
    std::cout << container << std::endl;
	// добавление элемента 30 в конец контейнера
    container.push_back(30);
	// вывод содержимого контейнера на экран
	// (ожидаемый результат: 10, 0, 1, 3, 20, 5, 7, 8, 9, 30)
    std::cout << container << std::endl;
    /*for (auto iter = container.begin(); iter != container.end(); ++iter){
        std::cout << *iter << std::endl;
    }*/
	return 0;
}
