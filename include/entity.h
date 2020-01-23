#pragma once

#include <SFML/Graphics.hpp>

#include <animation.h>

namespace rl {

class Entity
{
public:
    Entity();

    virtual void update();
    virtual void draw(sf::RenderTarget &target);

    static float s_MoveUnit; // pixel per second
    static float getMovePerFrame(float speed);

    float x, y;   // position of a entity
    float speed;  // speed of a entity
    float dir;    // angle
    bool visible; // TODO: impl
    //
    sf::Clock clk;
};

}