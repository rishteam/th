#include <entity.h>
#include <utils.h>
#include <log.h>

namespace rl {

// std::string Entity::s_class = "Entity";

Entity::Entity()
{
    x = y = 0.f;
    speed = 1.f;
    dir = 0.f;
    visible = true;
    //
    collideType = Entity::CollideType::None;
}

void Entity::update()
{
}

void Entity::draw(sf::RenderTarget &target)
{
}

// Collision related
bool Entity::isCollideWith(const Entity &rhs)
{
    if(collideType == Circle)
    {
        if(rhs.collideType == Circle)
        {
            float dis = collideData.circle.radius + rhs.collideData.circle.radius;
            dis = dis * dis;
            // fmt::printf("%.2f %.2f / %.2f\n", collideData.circle.radius, rhs.collideData.circle.radius,
            //     sqrt(distance(sf::Vector2f(getCentX(), getCentY()), sf::Vector2f(rhs.getCentX(), rhs.getCentY()))));
            float tmp = distance(sf::Vector2f(getCentX(), getCentY()), sf::Vector2f(rhs.getCentX(), rhs.getCentY()));
            return tmp < dis;
        }
        else
        {
            RL_ERROR("Circle collide with other shapre has not implemented yet\n");
        }
    }
    else if(collideType == Rectangle)
    {
        RL_ERROR("Rectangle collision has not implemented yet\n");
    }
    else if(collideType == Polygon)
    {
        RL_ERROR("Polygon collision has not implemented yet\n");
    }
    return false;
}

}