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

    static float s_MoveUnit;

    float x, y;
    float speed;
    float dir;
    bool visible; // TODO: impl
    //
    sf::Clock clk;
};

}