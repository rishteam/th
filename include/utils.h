#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

namespace rl {

#if defined(_WIN32)
    #define M_PI 3.14159265358979323846
#endif

constexpr double RAD2DEG = 180.0 / M_PI;
constexpr double DEG2RAD = M_PI / 180.0;

// TODO: test this
// void rotateByPoint(sf::Vector2f &t, sf::Vector2f p, float angle)
// {
//     float now = atan2(t.y-p.y, t.x-p.x);
//     now += angle;
//     float radius = sqrt(pow(t.x-p.x, 2) + pow(t.y-p.y, 2));
//     t.x += radius * cos(now);
//     t.y += radius * sin(now);
// }

}