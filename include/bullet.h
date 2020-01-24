#pragma once

#include <cmath>
#include <list>

#include <entity.h>

namespace rl {

class Bullet : public Entity
{
public:
    enum BulletType
    {
        None,
        Disappear,    // TODO
        Rebound,      // TODO
        Script,       // ???
        //
        BulletTypeCount // count
    };
    enum BulletShotByType
    {
        Nobody,
        Player,
        NPCnormal,
        NPCspecial,
        //
        BulletShotByTypeCount // count
    };

    Bullet();
    Bullet(BulletType type_, BulletShotByType shotByType_,
           float x_, float y_, float size_, float dir_);

    virtual void update() override;
    virtual void draw(sf::RenderTarget& target) override;

    bool valid;
    float size;
    BulletType type;
    BulletShotByType shotByType;
private:

    Animation bullet;
};

class BulletManager
{
public:
    void addBullet(Bullet::BulletType type, Bullet::BulletShotByType shotByType,
                   float x, float y, float size, float dir)
    {
        bulletList.push_back(Bullet(type, shotByType, x, y, size, dir));
    }
    //
    void update();
    void draw(sf::RenderTarget &target);

    void collideWith(const Entity &ent);

    std::list<Bullet> bulletList;
};
}