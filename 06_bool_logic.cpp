// ============================================================
// 06_bool_logic.cpp
// Тема: bool, boolalpha, логические операторы &&, ||, !
// ============================================================

#include <iostream>
#include <string>

int main() {
  // ========================================================
  // ТИП bool
  // ========================================================
  //
  // bool хранит одно из двух значений: true или false.
  // Размер: обычно 1 байт (хотя стандарт не фиксирует).
  // При выводе через cout по умолчанию печатается 1 или 0.

  bool isAdult = true;
  bool hasTicket = false;

  std::cout << "=== Вывод bool по умолчанию ===\n";
  std::cout << "isAdult:   " << isAdult << "\n";     // 1
  std::cout << "hasTicket: " << hasTicket << "\n\n"; // 0

  // boolalpha — манипулятор, переключает вывод на "true"/"false"
  std::cout << "=== Вывод с boolalpha ===\n";
  std::cout << std::boolalpha;
  std::cout << "isAdult:   " << isAdult << "\n";     // true
  std::cout << "hasTicket: " << hasTicket << "\n\n"; // false
  // Вернуть обратно: std::noboolalpha

  // ========================================================
  // ОПЕРАТОРЫ СРАВНЕНИЯ (возвращают bool)
  // ========================================================
  int age = 20;
  std::cout << "=== Операторы сравнения (age = 20) ===\n";
  std::cout << "age == 20 : " << (age == 20) << "\n";
  std::cout << "age != 18 : " << (age != 18) << "\n";
  std::cout << "age >  18 : " << (age > 18) << "\n";
  std::cout << "age <  18 : " << (age < 18) << "\n";
  std::cout << "age >= 20 : " << (age >= 20) << "\n";
  std::cout << "age <= 20 : " << (age <= 20) << "\n\n";

  // ========================================================
  // ЛОГИЧЕСКИЙ И (&&)
  // ========================================================
  //
  // a && b — истина только если ОБА условия истинны.
  // Таблица истинности:
  //   true  && true  = true
  //   true  && false = false
  //   false && true  = false
  //   false && false = false
  //
  // Особенность: "короткое замыкание" (short-circuit evaluation).
  // Если левый операнд false — правый НЕ вычисляется.

  bool isOver18 = (age >= 18); // true
  bool hasPassport = true;
  bool canFly = isOver18 && hasPassport;

  std::cout << "=== Логическое И (&&) ===\n";
  std::cout << "Возраст >= 18: " << isOver18 << "\n";
  std::cout << "Есть паспорт:  " << hasPassport << "\n";
  std::cout << "Может летать:  " << canFly << "\n\n";

  // ========================================================
  // ЛОГИЧЕСКИЙ ИЛИ (||)
  // ========================================================
  //
  // a || b — истина если ХОТЯ БЫ одно условие истинно.
  // Таблица истинности:
  //   true  || true  = true
  //   true  || false = true
  //   false || true  = true
  //   false || false = false
  //
  // Короткое замыкание: если левый true — правый не вычисляется.

  bool hasCash = false;
  bool hasCard = true;
  bool canPay = hasCash || hasCard;

  std::cout << "=== Логическое ИЛИ (||) ===\n";
  std::cout << "Есть наличные: " << hasCash << "\n";
  std::cout << "Есть карта:    " << hasCard << "\n";
  std::cout << "Может платить: " << canPay << "\n\n";

  // ========================================================
  // ЛОГИЧЕСКОЕ НЕ (!)
  // ========================================================
  //
  // !a — инвертирует значение.
  //   !true  = false
  //   !false = true

  bool isDoorLocked = true;
  bool isDoorUnlocked = !isDoorLocked;

  std::cout << "=== Логическое НЕ (!) ===\n";
  std::cout << "Дверь закрыта:    " << isDoorLocked << "\n";
  std::cout << "Дверь не закрыта: " << isDoorUnlocked << "\n\n";

  // ========================================================
  // КОМБИНИРОВАННЫЙ ПРИМЕР: допуск в кино
  // ========================================================
  int visitorAge = 15;
  bool withParent = true;
  std::string movieRating = "16+";

  // Фильм 16+: пустить если возраст >= 16 ИЛИ (с родителем И >= 12)
  bool allowed = (visitorAge >= 16) || (withParent && visitorAge >= 12);

  std::cout << "=== Допуск в кино (возраст=" << visitorAge
            << ", с родителем=" << withParent << ", рейтинг=" << movieRating
            << ") ===\n";
  std::cout << "Допуск разрешён: " << allowed << "\n\n";

  return 0;
}
