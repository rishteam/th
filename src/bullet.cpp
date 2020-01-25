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
            if (b.x <= -5 || b.x >= g_WindowWidth + 5
            || b.y <= -5 || b.y >= g_WindowHeight + 5)
            {
                bulletList.erase(it++);
            }
            else
                it++;
        }
        break;

        case Bullet::BulletType::Rebound:
            RL_ERROR("Bullet::BulletType::Rebound has not implemented yet.\n");
        break;

        case Bullet::BulletType::Script:
            RL_ERROR("Bullet::BulletType::Script has not implemented yet.\n");
        break;
        }
    }
}

void BulletManager::draw(sf::RenderTarget &target)
{
    for(auto &b : bulletList)
        b.draw(target);
}

void BulletManager::collideWith(const Entity &ent)
{
    for(auto it = bulletList.begin(); it != bulletList.end();)
    {
        Bullet &b = *it;
        if(b.isCollideWith(ent))
        {
            bulletList.erase(it++);
        }
        else
            it++;
    }
}

//----------------------------------------------------------------------------------
// Bullet

float Bullet::s_MoveUnit = 1000;

Bullet::Bullet()
{
    // Bullet::s_class = "Bullet";
    //
    bullet.setInfo("round_red", 1, "assets/bullet/", "round_r.png");
    bullet.loadRes();
    //
    size = 1.f;
    valid = true;
    width = height = 8;
    // type
    type = BulletType::None;
    shotByType = BulletShotByType::Nobody;
    // Collision
    collideType = Bullet::CollideType::Circle;
    collideData.circle.radius = std::max(width, height) * size;
}

Bullet::Bullet(BulletType type_, BulletShotByType shotByType_,
               float x_, float y_, float size_, float dir_)
    : Bullet()
{
    x = x_;
    y = y_;
    size = size_;
    dir = dir_;
    //
    type = type_;
    shotByType = shotByType_;
}

void Bullet::update()
{
    x += getMovePerFrame<Bullet>(speed) * cos(dir * DEG2RAD);
    y += getMovePerFrame<Bullet>(speed) * sin(dir * DEG2RAD);
}

void Bullet::draw(sf::RenderTarget &target)
{
    bullet.setPosition(x, y);
    bullet.setScale(sf::Vector2f(size, size));
    bullet.draw(target);
}

}