#pragma once

#include <SFML/Graphics.hpp>

#include <core.h>
#include <entity.h>

namespace rl {

class Player : public Entity
{
public:
    Player();


    virtual void update() override;
    virtual void draw(sf::RenderTarget &target) override;

    enum PlayerDir
    {
        DirNone = 0,
        DirRight,
        DirUpRight,
        DirUp,
        DirUpLeft,
        DirLeft,
        DirDownLeft,
        DirDown,
        DirDownRight,
        //
        DirCount // count
    };

    static std::string debugPlayerDir[DirCount];

private:
    void processInput();
    bool isLeft(PlayerDir dir) { return playerDir == DirLeft || playerDir == DirUpLeft || playerDir == DirDownLeft; }
    bool isRight(PlayerDir dir) { return playerDir == DirRight || playerDir == DirUpRight || playerDir == DirDownRight; }

    PlayerDir playerDir, preDir;
    Animation hover, move;
    Animation *nowAni;
};

}