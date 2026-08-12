// ============================================================
// 03_float_types.cpp
// Тема: вещественные типы, деление, точность, накопление ошибки
// ============================================================

#include <cfloat>  // FLT_MAX, DBL_MAX, FLT_EPSILON, ...
#include <cmath>   // std::fabs, std::round
#include <iomanip> // std::setprecision
#include <iostream>
#include <limits> // std::numeric_limits

int main() {
  // ========================================================
  // СЕМЕЙСТВО ВЕЩЕСТВЕННЫХ ТИПОВ
  // ========================================================
  //
  //  float       — 4 байта, ~7 значащих десятичных цифр
  //  double      — 8 байт, ~15-16 значащих цифр   <- по умолчанию
  //  long double — >= 8 байт (на x86/MSVC = 8, на GCC x64 = 16 байт)
  //
  // Литералы:
  //   3.14       — double
  //   3.14f      — float   (суффикс f или F)
  //   3.14L      — long double (суффикс L)

  std::cout << "=== Размеры вещественных типов ===\n";
  std::cout << "float:       " << sizeof(float) << " байт\n";
  std::cout << "double:      " << sizeof(double) << " байт\n";
  std::cout << "long double: " << sizeof(long double) << " байт\n\n";

  std::cout << "=== Диапазоны ===\n";
  std::cout << "FLT_MAX = " << FLT_MAX << "\n";
  std::cout << "DBL_MAX = " << DBL_MAX << "\n";
  std::cout << "FLT_EPSILON = " << FLT_EPSILON
            << "  (наименьшее x такое, что 1.0f + x != 1.0f)\n";
  std::cout << "DBL_EPSILON = " << DBL_EPSILON << "\n\n";

  // ========================================================
  // ЦЕЛОЧИСЛЕННОЕ ДЕЛЕНИЕ vs ВЕЩЕСТВЕННОЕ
  // ========================================================
  int apples{7};
  int persons{2};

  // Деление int на int — результат int, дробная часть ОТБРАСЫВАЕТСЯ
  int intResult{apples / persons};
  // Чтобы получить double, достаточно привести ОДИН из операндов:
  double doubleResult1{static_cast<double>(apples) / persons};
  double doubleResult2{apples / static_cast<double>(persons)};
  // double doubleResult3 = (double)apples / persons;  // C-style cast (не
  // рекомендуется)

  std::cout << "=== Деление 7 / 2 ===\n";
  std::cout << "int    / int    = " << intResult << "  <- дробь потеряна!\n";
  std::cout << "double / int    = " << doubleResult1 << "\n";
  std::cout << "int    / double = " << doubleResult2 << "\n\n";

  // Практический пример: средняя оценка студента
  int totalScore = 85 + 90 + 78;
  int subjects{3};
  double average = static_cast<double>(totalScore) / subjects;
  std::cout << "Средний балл: " << average << "\n\n";

  // ========================================================
  // УПРАВЛЕНИЕ ТОЧНОСТЬЮ ВЫВОДА
  // ========================================================
  double long_d{1.0 / 3};
  float long_f{1.0 / 3};

  std::cout << "=== Точность вывода long_d ===\n";
  std::cout << "По умолчанию:        " << long_d << "\n"; // 6 значащих цифр
  std::cout << std::setprecision(10) << "long_d setprecision(10):    " << long_d
            << "\n";
  std::cout << std::setprecision(20) << "long_d setprecision(20):    " << long_d
            << "\n";
  std::cout << std::setprecision(10) << "long_f setprecision(10):    " << long_f
            << "\n";
  std::cout << std::setprecision(20) << "long_f setprecision(20):    " << long_f
            << "\n";

  // ========================================================
  // ПРОБЛЕМА ТОЧНОСТИ: 0.1 + 0.2 != 0.3
  // ========================================================
  // Числа с плавающей точкой хранятся в двоичной форме.
  // 0.1 в двоичной — бесконечная дробь, поэтому в памяти — приближение.

  double x{0.1 + 0.2};
  double expected{0.3};

  std::cout << "=== Ловушка 0.1 + 0.2 ===\n";
  std::cout << std::setprecision(17);
  std::cout << "0.1 + 0.2         = " << x << "\n";
  std::cout << "0.3               = " << expected << "\n";
  std::cout << "0.1 + 0.2 == 0.3  ? " << (x == expected ? "true" : "false")
            << "  <- НИКОГДА не сравнивайте double через ==\n\n";

  // Правильное сравнение: через эпсилон
  double eps{1e-9};
  bool almostEqual{std::fabs(x - expected) < eps};
  std::cout << "std::fabs(x - 0.3) < 1e-9 ? "
            << (almostEqual ? "true" : "false") << "  <- правильный способ\n\n";

  // ========================================================
  // СПЕЦИАЛЬНЫЕ ЗНАЧЕНИЯ
  // ========================================================
  double posInf{std::numeric_limits<double>::infinity()};
  double negInf{-std::numeric_limits<double>::infinity()};
  double nanVal{std::numeric_limits<double>::quiet_NaN()};

  std::cout << "=== Специальные значения ===\n";
  std::cout << "+Infinity: " << posInf << "\n";
  std::cout << "-Infinity: " << negInf << "\n";
  std::cout << "NaN:       " << nanVal << "\n";
  std::cout << "1.0 / 0.0  (double) = " << (1.0 / 0.0) << "\n";  // +inf
  std::cout << "-1.0 / 0.0 (double) = " << (-1.0 / 0.0) << "\n"; // -inf
  // int деление на ноль — это UB (и краш на практике), не делайте так.
}
