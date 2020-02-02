#pragma once

#include <functional>
//
#include <log.h>
#include <utils.h>

namespace rl {

// TODO: implement rect, polygon collision

enum CollideType
{
    None,
    Circle,
    Rectangle, // TODO
    Polygon    // TODO
};

struct CircleCollideData
{
    float x, y;
    float radius;
};
struct RectangleCollideData
{
    float x, y;
    float width, height;
};
struct PolygonCollideData
{
    //TODO: implment PloygonCollideData
};
union CollideData {
    CircleCollideData circle;
    RectangleCollideData rectangle;
    PolygonCollideData polygon;
};

struct Collider
{
    CollideType type;
    CollideData data;
};

// Collide handle functions
bool defaultCollide(const Collider &lc, const Collider &rc);
bool circleCollideCircle(const Collider &lc, const Collider &rc);

// Interface
using CollideHandler = std::function<bool(const Collider &, const Collider &)>;
bool isCollideWith(const Collider &lc, const Collider &rc, CollideHandler handler=nullptr);

}