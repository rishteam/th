#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

namespace rl {

constexpr double DEG2RAD = 180.0 / M_PI;
constexpr double RAD2DEG = M_PI / 180.0;

// TODO: test this
void rotateByPoint(sf::Vector2f &t, sf::Vector2f p, float angle)
{
    float now = atan2(t.y-p.y, t.x-p.x);
    now += angle;
    float radius = sqrt(pow(t.x-p.x, 2) + pow(t.y-p.y, 2));
    t.x += radius * cos(now);
    t.y += radius * sin(now);
}

}