#pragma once

#include <cmath>
#include <list>

#include <entity.h>

namespace rl {

// Globals

extern const char * g_BulletShotBTypeName[];
extern const char * g_BulletTypeName[];

//
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
           float x_, float y_, float size_, float dir_, float speed_);

    virtual void update() override;
    virtual void draw(sf::RenderTarget& target) override;

    virtual float getX() const override
    {
        return x - width * size / 2;
    }
    virtual float getY() const override
    {
        return y - height * size / 2;
    }
    virtual float getCentX() const override
    {
        return x;
    }
    virtual float getCentY() const override
    {
        return y;
    }

    int width, height;

    bool valid;
    float size;
    BulletType type;
    BulletShotByType shotByType;
    // Collision related
    Collider body;
private:

    Animation bullet;
};

class BulletManager
{
public:
    BulletManager()
    {
        speed = 1.f;
    }
    void addBullet(Bullet::BulletType type, Bullet::BulletShotByType shotByType,
                   float x, float y, float size, float dir, float speed_)
    {
        speed = speed_;
        bulletList.push_back(Bullet(type, shotByType, x, y, size, dir, speed));
    }
    //
    void update();
    void draw(sf::RenderTarget &target);

    bool collideWith(const Entity &ent);

    bool empty() { return bulletList.empty(); }

    float speed;

    std::list<Bullet> bulletList;
};

} // end of namespace