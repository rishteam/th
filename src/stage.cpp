#include <stage.h>
#include <log.h>

namespace rl {

Stage1::Stage1(Player &p)
    : player(p)
{
    state = STG1;
    // stgs
}

void Stage1::update()
{
    switch(state)
    {
    case Stage1::STG1:
        stg1();
    break;
    case Stage1::STG2:
        stg2();
    break;
    case Stage1::STG3:
        stg3();
    break;
    }

    for (auto &i : bu)
        i.update();

    for(auto &i : bu)
        if(i.collideWith(player))
        {
            player.reset();
            stg1_state = Stg1Over;
            RL_DEBUG("Player is dead");
        }
}

void Stage1::draw(sf::RenderTarget &target)
{
    for (auto &i : bu)
        i.draw(target);
}

void Stage1::stg1()
{
    switch(stg1_state)
    {
    case Stg1Gen:
    {
        // RL_DEBUG("stg1_state = {}", "Stg1Gen");
        for (int num = 0; num < 4; num++)
        {
            float x = randf_range(90, 780), y = randf_range(100, 320);
            fmt:printf("%f %f\n", x, y);

            bu.push_back(BulletManager());
            BulletManager &m = bu.back();

            for (int i = 0; i < 10; i++)
            {
                float rad = randi(1, 360) * DEG2RAD;
                float r = 10;
                m.addBullet(Bullet::BulletType::Disappear, Bullet::BulletShotByType::NPCnormal,
                            x + r * cos(rad), y + r * sin(rad), 1.f, rand() % 360, 0.3f);
            }
        }
        stg1_state = Stg1Wait;
    }
    break;

    case Stg1Wait:
    {
        // RL_DEBUG("stg1_state = {}", "Stg1Wait");

        if(stg1_clk.getElapsedTime().asSeconds() > 1.0)
        {
            stg1_clk.restart();
            stg1_genCnt++;
            if(stg1_genCnt < 10)
            {
                stg1_state = Stg1Gen;
                return;
            }
        }

        bool pass = true;
        for(auto &i : bu)
            pass &= i.empty();
        //
        if(pass)
            stg1_state = Stg1Over;
    }
    break;

    case Stg1Over:
        // RL_DEBUG("stg1_state = {}", "Stg1Over");
        while(!bu.empty())
            bu.pop_back();
        break;
    }
}

void Stage1::stg2()
{
}

void Stage1::stg3()
{
}

}