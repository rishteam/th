#pragma once

#include <entity.h>

namespace rl {

class Bullet : public Entity
{
public:
    Bullet();
    Bullet(float x_, float y_);

    virtual void update() override;
    virtual void draw(sf::RenderTarget& target) override;

    float size;
private:
    Animation bullet;
};

}