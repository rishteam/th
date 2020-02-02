#pragma once

#include <vector>

#include <player.h>
#include <bullet.h>
#include <utils.h>

namespace rl {

class Stage1
{
public:
    Stage1(Player &p);
    void update();
    void draw(sf::RenderTarget &target);

    Player &player;
    //
    // stg1
    enum Stg1States
    {
        Stg1Gen,
        Stg1Wait,
        Stg1Over,
    };
    Stg1States stg1_state;
    int stg1_genCnt = 0;
    sf::Clock stg1_clk;
    void stg1();

    // stg2
    void stg2();

    // stg3
    void stg3();

    enum StageState
    {
        STG1, // 上半部隨機彈
        STG2, // sniper
        STG3  // 旋轉
    };
    StageState state;

    std::vector<BulletManager> bu;
};

}