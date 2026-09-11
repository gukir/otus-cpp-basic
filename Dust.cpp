#include "Dust.hpp"
#include <cmath>
#include <random>

Dust::Dust(const Point &center, double radius, const Velocity &velocity, const Color &color, double lifetime) :
      cent{center}, rad{radius}, vel{velocity}, col{color}, ltime{lifetime}, maxltime{ltime} {}

void Dust::update(double timePerTick) {
    cent = cent + vel.vector() * timePerTick;
    ltime -= timePerTick;
}

bool Dust::isAlive() const {
    return ltime > 0.;
}

void Dust::draw(Painter &painter) const {
    if (!isAlive()) {
        return;
    }
    const double Kdamping = ltime / maxltime;
    const Color color(col.red() * Kdamping, col.green() * Kdamping, col.blue() * Kdamping);
    painter.draw(cent, rad * Kdamping, color);
}

void spawnDust(std::vector<Dust> &fragments, const Point &center, const Point &normal, const Color &color, double impactSpeed, size_t count){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distirb(-1., 1.);

    const double base_angle = std::atan2(normal.y, normal.x);
    for (size_t i = 0; i < count; ++i){
        const double angle = base_angle + M_PI * std::signbit(distirb(gen)) + M_PI / 6 * (distirb(gen));
        const double speed = impactSpeed * (1. + distirb(gen)) / 2;
        const Velocity vel{Point{std::cos(angle), std::sin(angle)} * speed};
        const double radius = 10 * (1. + distirb(gen));
        const double lifetime = (1. + distirb(gen)) / 2;
        fragments.emplace_back(center, radius, vel, color, lifetime);
    }
}
