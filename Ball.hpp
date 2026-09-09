#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
public:
    Ball();
    Ball(const Point &center, double radius, const Velocity &velocity, const Color &color);
    void setVelocity(const Velocity& velocity);
    void setColor(const Color& color);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
private:
    Point cent{};
    double rad{};
    Velocity vel{};
    Color col{};
};
