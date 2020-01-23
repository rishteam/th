#include <bullet.h>
#include <utils.h>

namespace rl {

Bullet::Bullet()
{
    bullet.setInfo("round_red", 1, "assets/bullet/", "round_r.png");
    bullet.loadRes();
    //
    size = 1.f;
    valid = true;

    Bullet::s_MoveUnit = 1000;
}

Bullet::Bullet(float x_, float y_)
    : Bullet()
{
    x = x_;
    y = y_;
}

void Bullet::update()
{
    x += Bullet::getMovePerFrame(speed) * cos(dir * DEG2RAD);
    y += Bullet::getMovePerFrame(speed) * sin(dir * DEG2RAD);
}

void Bullet::draw(sf::RenderTarget &target)
{
    bullet.setPosition(x, y);
    bullet.setScale(sf::Vector2f(size, size));
    bullet.draw(target);
}

}