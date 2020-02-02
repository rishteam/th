#pragma once

#include <SFML/Graphics.hpp>

#include <core.h>
#include <entity.h>
#include <collision.h>

namespace rl {

class Player : public Entity
{
public:
    Player();
    Player(float x_, float y_);

    static float s_MoveUnit; // pixel per second

    virtual void update() override;
    virtual void draw(sf::RenderTarget &target) override;
    void reset()
    {
        x = 416;
        y = 700;
    }

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
    // Judge point collision
    float judgePointX , judgePointY , judgePointRadius;
    // Body collision
    float bodyColX, bodyColY, bodyColW, bodyColH;
    float size;
    float width, height; // TODO

    // Colliders
    Collider body;

    bool stateChanged;

    virtual float getX() const override
    {
        return x - judgePointX;
    }
    virtual float getY() const override
    {
        return y - judgePointY;
    }

    virtual float getCentX() const override
    {
        return x;
    }
    virtual float getCentY() const override
    {
        return y;
    }

private:
    void processInput();
    void processMove();
    // helper
    bool isLeft(PlayerDir dir) { return playerDir == DirLeft || playerDir == DirUpLeft || playerDir == DirDownLeft; }
    bool isRight(PlayerDir dir) { return playerDir == DirRight || playerDir == DirUpRight || playerDir == DirDownRight; }

    PlayerDir playerDir, preDir;
    bool slow;
    Animation hover, move;
    Animation *nowAni;
};

}