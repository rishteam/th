#pragma once

#include <SFML/Graphics.hpp>

#include <animation.h>
#include <collision.h>
#include <utils.h>
#include <log.h>

namespace rl {

extern int g_WindowWidth, g_WindowHeight; // workaround

class Entity
{
public:
    // static std::string s_class;
    // std::string id;

    Entity();

    virtual void update();
    virtual void draw(sf::RenderTarget &target);

    //
    // Entity Coordinate
    // Get x coordinate of left upper corner
    virtual float getX() const { return x; }
    // Get y coordinate of left upper corner
    virtual float getY() const { return y; }
    // Get x coordinate of the center
    virtual float getCentX() const { return x; }
    // Get y coordinate of the center
    virtual float getCentY() const { return y; }
    //
    Collider judge;

    float x, y;   // center coordinate
    float speed;  // speed of a entity
    float dir;    // angle
    bool visible; // TODO: impl
    //
    sf::Clock clk;
};

}