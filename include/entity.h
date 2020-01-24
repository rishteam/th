#pragma once

#include <SFML/Graphics.hpp>

#include <animation.h>

namespace rl {

// TODO: implement rect, polygon collision

class Entity
{
public:
    Entity();

    virtual void update();
    virtual void draw(sf::RenderTarget &target);

    static float s_MoveUnit; // pixel per second
    static float getMovePerFrame(float speed);

    // Collision reloated
    bool isCollideWith(const Entity &rhs);
    enum CollideType
    {
        None,
        Circle,
        Rectangle, // TODO
        Polygon    // TODO
    };
    CollideType collideType;

    struct CircleCollideData
    {
        float radius;
    };
    struct RectangleCollideData
    {
        float width, height;
    };
    struct PolygonCollideData
    {
        //TODO: implment PloygonCollideData
    };
    union CollideData
    {
        CircleCollideData circle;
        RectangleCollideData rectangle;
        PolygonCollideData polygon;
    };
    CollideData collideData;
    //

    float x, y;   // position of a entity
    float speed;  // speed of a entity
    float dir;    // angle
    bool visible; // TODO: impl
    //
    sf::Clock clk;
};

}