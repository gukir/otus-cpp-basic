#include "Ball.hpp"
#include <cmath>

Ball::Ball() = default;

Ball::Ball(const Point& center, double radius, const Velocity& velocity, const Color& color)
    : cent{center}, rad{radius}, vel{velocity}, col{color} {}


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
