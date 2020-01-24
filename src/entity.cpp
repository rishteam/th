#include <entity.h>
#include <game.h>
#include <utils.h>
#include <log.h>

namespace rl {

float Entity::s_MoveUnit = 1.f;

float Entity::getMovePerFrame(float speed)
{
    return (Entity::s_MoveUnit * speed) / Game::s_fps;
}

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
            RL_DEBUG("{} {}", collideData.circle.radius, rhs.collideData.circle.radius);
            // RL_DEBUG("{} {}\n", distance(sf::Vector2f(x, y), sf::Vector2f(rhs.x, rhs.y)), dis);
            return distance(sf::Vector2f(x, y), sf::Vector2f(rhs.x, rhs.y)) < dis;
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