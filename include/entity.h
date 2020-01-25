#pragma once

#include <SFML/Graphics.hpp>

#include <animation.h>

namespace rl {

extern int g_WindowWidth, g_WindowHeight; // workaround

// TODO: implement rect, polygon collision
class Entity
{
public:
    // static std::string s_class;
    // std::string id;

    Entity();

    virtual void update();
    virtual void draw(sf::RenderTarget &target);

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

    // Get x coordinate of left upper corner
    virtual float getX() const { return x; }
    // Get y coordinate of left upper corner
    virtual float getY() const { return y; }
    // Get x coordinate of the center
    virtual float getCentX() const { return x; }
    // Get y coordinate of the center
    virtual float getCentY() const { return y; }
    //
    float x, y;   // left upper corner
    // float cx, cy; // center coordinate of a obj
    float speed;  // speed of a entity
    float dir;    // angle
    bool visible; // TODO: impl
    //
    sf::Clock clk;
};

}