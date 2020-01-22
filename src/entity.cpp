#include <entity.h>

namespace rl {

float Entity::s_MoveUnit = 1.f;

Entity::Entity()
{
    x = y = 0.f;
    speed = 1.f;
    dir = 0.f;
    visible = true;
}

void Entity::update()
{
}

void Entity::draw(sf::RenderTarget &target)
{
}

}