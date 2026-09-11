#pragma once
#include "Color.hpp"
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"
#include <vector>

class Dust {
  public:
    Dust(const Point &center, double radius, const Velocity &velocity, const Color &color, double lifetime);
    void update(double timePerTick);
    bool isAlive() const;
    void draw(Painter &painter) const;
  private:
    Point cent{};
    double rad{};
    Velocity vel{};
    Color col{};
    double ltime{};
    double maxltime{};
};


void spawnDust(std::vector<Dust> &fragments, const Point &center, const Point &normal, const Color &color, double impactSpeed, size_t count = 10);
