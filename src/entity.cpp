#include <entity.h>

namespace rl {

// std::string Entity::s_class = "Entity";

Entity::Entity()
{
    x = y = 0.f;
    speed = 1.f;
    dir = 0.f;
    visible = true;
    //
    judge.type = CollideType::None;
}

void Entity::update()
{
}

void Entity::draw(sf::RenderTarget &target)
{
}

}