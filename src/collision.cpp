#include <collision.h>

namespace rl {

bool defaultCollide(const Collider &lc, const Collider &rc)
{
    RL_DEBUG("Go to default collide handler");
    return false;
}

bool circleCollideCircle(const Collider &lc, const Collider &rc)
{
    auto & lData = lc.data.circle, &rData = rc.data.circle;
    float dis = lData.radius + rData.radius;
    dis = dis * dis; // dis^2
    float now = distanceSquare(sf::Vector2f(lData.x, lData.y), sf::Vector2f(rData.x, rData.y));
    return now < dis;
}

bool isCollideWith(const Collider &lc, const Collider &rc, CollideHandler handler)
{
    if (!handler) handler = defaultCollide;
    if (lc.type == Circle)
    {
        if (rc.type == Circle)
        {
            handler = circleCollideCircle;
        }
        else
        {
            RL_ERROR("Circle collide with other shapre has not implemented yet\n");
        }
    }
    else if (lc.type == Rectangle)
    {
        RL_ERROR("Rectangle collision has not implemented yet\n");
    }
    else if (lc.type == Polygon)
    {
        RL_ERROR("Polygon collision has not implemented yet\n");
    }
    return handler(lc, rc);
}

}

