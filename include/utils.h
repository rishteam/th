#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <utility>

#include <SFML/System.hpp>

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

// Get the distance of two points (sf::Vector2f)
float distanceSquare(const sf::Vector2f a, const sf::Vector2f b);

// random float in [0.0, 1.0]
float randf();

// random int in a range [lo, up]
int randi(int lo, int up);

// random float in specified range [lo, up]
float randf_range(float lo, float up);

}