#include <game.h>
#include <bullet.h>
#include <utils.h>
#include <core.h>
#include <log.h>

namespace rl {

//----------------------------------------------------------------------------------
// Bullet Manager
void BulletManager::update()
{
    // Update all bullets
    for(auto &b : bulletList)
        b.update();
    //
    for(auto it = bulletList.begin(); it != bulletList.end();)
    {
        Bullet &b = *it;
        //
        RL_ASSERT(b.type != Bullet::BulletType::None, "The Bullet::type is unknown {}", b.type);
        switch(b.type)
        {
        case Bullet::BulletType::Disappear:
        {
            if (b.x <= -5 || b.x >= Game::s_WindowWidth + 5
            || b.y <= -5 || b.y >= Game::s_WindowHeight + 5)
            {
                bulletList.erase(it++);
            }
            else
                it++;
        }
        break;

        case Bullet::BulletType::Rebound:
            RL_WARN("Bullet::BulletType::Rebound isn't supported\n");
        break;

        case Bullet::BulletType::Script:
            RL_WARN("Bullet::BulletType::Script isn't supported\n");
        break;
        }
    }
}

void BulletManager::draw(sf::RenderTarget &target)
{
    for(auto &b : bulletList)
        b.draw(target);
}

//----------------------------------------------------------------------------------
// Bullet
Bullet::Bullet()
{
    bullet.setInfo("round_red", 1, "assets/bullet/", "round_r.png");
    bullet.loadRes();
    //
    size = 1.f;
    valid = true;
    // type
    type = BulletType::None;
    shotByType = BulletShotByType::Nobody;
    // attributes
    Bullet::s_MoveUnit = 1000;
}

Bullet::Bullet(BulletType type_, BulletShotByType shotByType_,
               float x_, float y_, float size_, float dir_)
    : Bullet()
{
    x = x_;
    y = y_;
    size = size_;
    dir = dir_;
    type = type_;
    shotByType = shotByType_;

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