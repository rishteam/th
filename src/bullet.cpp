#include <bullet.h>

namespace rl {

Bullet::Bullet()
{
    bullet.setInfo("round_red", 1, "assets/bullet/", "round_r.png");
    bullet.loadRes();
    size = 1.f;
}

Bullet::Bullet(float x_, float y_)
    : Bullet()
{
    x = x_;
    y = y_;
}

void Bullet::update()
{

}

void Bullet::draw(sf::RenderTarget &target)
{
    bullet.setPosition(x, y);
    bullet.setScale(sf::Vector2f(size, size));
    bullet.draw(target);
}

}