// Для использования std::fstream
#include <fstream>
#include <iostream>
#include <string>

void example1() {
    std::fstream fso;
    fso.open("ex_file.txt", std::fstream::out); //| std::fstream::app);
    fso << " This 12 34 is a simple example of file output" << std::endl;
    fso << " One more line";
    fso.close();

    std::string single_world, w2;
    int a, b;

    std::fstream fsi;
    fsi.open("ex_file.txt", std::fstream::in);

    fsi >> single_world;
    fsi >> a >> b;
    fsi >> w2;

    fsi.close();

    std::cout << single_world << std::endl;
    std::cout << a << " " << b << std::endl;
    std::cout << w2 << std::endl;

    // 2. Print file content
    fsi.open("ex_file.txt", std::fstream::in);

    std::string line;
    while (std::getline(fsi, line))
        std::cout << line << std::endl;
    fsi.close();
}

void pyramid(std::ofstream &out, int height) {
    std::cout << "Hello from the pyramid function!" << std::endl;
    std::cout << "The height is: " << height << std::endl;

    // Символ для "фона"
    char empty_symb = ' ';
    // Символ для "рисования"
    char star_symb = '*';

    // Ширина основания пирамиды
    const int size = 2 * height - 1;
    for (int row{0}; row < height; ++row) {
        // Ширина текущего уровня пирамиды
        const int line_size = 2 * (height - row) - 1;

        // Выводим пустые символы
        for (int empty{0}; empty < row; empty++)
            out << empty_symb;
        // Выводим звёздочки
        for (int stars{0}; stars < line_size; ++stars)
            out << star_symb;
        // Выводим пустые символы
        for (int empty{line_size + row}; empty < size; empty++)
            out << empty_symb;
        out << std::endl;
    }
}

int main(int, char *[]) {

    example1();

    std::ofstream file{"pyramid_out.txt"};
    pyramid(file, 5);

    return 0;
}
