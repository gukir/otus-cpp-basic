#include "Ball.hpp"
#include <cmath>
#include <fstream>

Ball::Ball() = default;

Ball::Ball(const Point& center, double radius, const Velocity& velocity, const Color& color)
    : cent{center}, rad{radius}, vel{velocity}, col{color} {}

std::istream& operator>>(std::istream& stream, Ball& variable) {

    Point center{};
    Point vel_vec{};
    Velocity velocity{};
    double radius{};
    Color color{};
    bool isCollidable;
    // Читаем координаты центра шара
    stream >> center;
    // Читаем координаты вектора скорости и записываем его
    stream >> vel_vec;
    velocity.setVector(vel_vec);
    // Читаем цвет шара
    stream >> color;
    // Читаем радиус шара
    stream >> radius;
    // Читаем свойство шара isCollidable, которое
    // указывает, требуется ли обрабатывать пересечение
    // шаров как столкновение. Если true - требуется.
    stream >> std::boolalpha >> isCollidable;
    variable.setCenter(center);
    variable.setColor(color);
    variable.setVelocity(velocity);
    variable.rad = radius;
    variable.isCollidable = isCollidable;
    return stream;
}

/**
 * Задает скорость объекта
 * @param velocity новое значение скорости
 */
void Ball::setVelocity(const Velocity& velocity) {
    vel = velocity;
}

/**
 * @return скорость объекта
 */
Velocity Ball::getVelocity() const {
    return vel.vector();
}

/**
 * @return будет ли отскок
 */
bool Ball::is_Collidable() const {
    return isCollidable;
}

/**
 * @brief Выполняет отрисовку объекта
 * @details объект Ball абстрагирован от конкретного
 * способа отображения пикселей на экране. Он "знаком"
 * лишь с интерфейсом, который предоставляет Painter
 * Рисование выполняется путем вызова painter.draw(...)
 * @param painter контекст отрисовки
 */
void Ball::draw(Painter& painter) const {
    painter.draw(cent, rad, col);
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Ball::setCenter(const Point& center) {
    cent = center;
}

/**
 * @return центр объекта
 */
Point Ball::getCenter() const {
    return cent;
}

/**
 * @brief Возвращает радиус объекта
 * @details обратите внимание, что метод setRadius()
 * не требуется
 */
double Ball::getRadius() const {
    return rad;
}

/**
 * @brief Возвращает массу объекта
 * @details В нашем приложении считаем, что все шары
 * состоят из одинакового материала с фиксированной
 * плотностью. В этом случае масса в условных единицах
 * эквивалентна объему: PI * radius^3 * 4. / 3.
 */
double Ball::getMass() const {
    return M_PI * std::pow(rad, 3.) * 4. / 3.;
}

/**
 * Задает цвет объекта
 * @param color новый цвет объекта
 */
void Ball::setColor(const Color& color) {
    col = color;
}
