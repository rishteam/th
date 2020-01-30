#pragma once

#include <SFML/Graphics.hpp>

#include <core.h>
#include <entity.h>

namespace rl {

class Player : public Entity
{
public:
    Player();

    static float s_MoveUnit; // pixel per second

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

    static float s_DirToAngle[DirCount];
    static std::string debugPlayerDir[DirCount];

    float judgePointX , judgePointY , judgePointRadius;
    float size;

    bool stateChanged;

    virtual float getCentX() const override
    {
        return x + judgePointX * size;
    }
    virtual float getCentY() const override
    {
        return y + judgePointY * size;
    }

private:
    void processInput();
    void processMove();
    // helper
    bool isLeft(PlayerDir dir) { return playerDir == DirLeft || playerDir == DirUpLeft || playerDir == DirDownLeft; }
    bool isRight(PlayerDir dir) { return playerDir == DirRight || playerDir == DirUpRight || playerDir == DirDownRight; }

    PlayerDir playerDir, preDir;
    Animation hover, move;
    Animation *nowAni;
};

}