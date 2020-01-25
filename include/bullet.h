#pragma once

#include <cmath>
#include <list>

#include <entity.h>

namespace rl {

class Bullet : public Entity
{
public:
    static float s_MoveUnit; // pixel per second

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
    void update(float x_, float y_)
    {
        x = x_;
        y = y_;
    }
    virtual void draw(sf::RenderTarget& target) override;

    virtual float getCentX() const override
    {
        fmt::printf("Bullet ver\n");
        return x + width * size;
    }
    virtual float getCentY() const override
    {
        return y + height * size;
    }

    int width, height;

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