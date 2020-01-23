#include <entity.h>
#include <game.h>

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
}

void Entity::update()
{
}

void Entity::draw(sf::RenderTarget &target)
{
}
}