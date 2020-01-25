#include <game.h>
#include <player.h>
#include <log.h>
#include <utils.h>

namespace rl {

std::string Player::debugPlayerDir[Player::DirCount] = {"DirNone", "DirRight", "DirUpRight", "DirUp", "DirUpLeft", "DirLeft", "DirDownLeft", "DirDown", "DirDownRight"};

float Player::s_DirToAngle[DirCount] = {
    -1.f,  // None
    0.f,   // right
    315.f, // up right
    270.f, // up
    225.f, // up left
    180.f, // left
    135.f, // down left
    90.f,  // down
    45.f   // down right
};

float Player::s_MoveUnit = 800;

Player::Player()
    : hover("reimu-hover", 4, "assets/player/", "reimu-hover{}.png"),
      move("reimu-move", 7, "assets/player/", "reimu-move{}.png")
{
    // Player::s_class = "Player";
    //
    playerDir = preDir = DirNone;
    nowAni = &hover;
    // player attributes
    x = g_WindowWidth/2;
    y = g_WindowHeight/2;
    //
    judgePointX = 15;
    judgePointY = 21;
    judgePointRadius = 4;

    size = 2.0f;
    // Collision
    collideType = Player::CollideType::Circle;
    collideData.circle.radius = (float)judgePointRadius * size;
    //
    // animation attributes
    hover.duration = 0.6f;
    hover.loop = true;
    hover.setScale(sf::Vector2f(size, size));

    move.duration = 0.8f;
    move.reverseDuration = 0.25f;
    move.loop = false;
    move.setScale(sf::Vector2f(size, size));
}

void Player::update()
{
    // Entity::update();
    //
    processInput();
    //
    processMove();
    // ----------------------------------------
    // Animation
    static bool moved = false;
    // select ani
    if(!moved && playerDir == DirNone)
        nowAni = &hover;
    else if(isLeft(playerDir) || isRight(playerDir))
    {
        moved = true;
        nowAni = &move;
        if(isRight(playerDir))
        {
            move.setOrigin(sf::Vector2f(move.getOrigInfo().width, 0.f));
            move.setScale(sf::Vector2f(-size, size));
        }
        else if(isLeft(playerDir))
        {
            move.setOrigin(sf::Vector2f(0.f, 0.f));
            move.setScale(sf::Vector2f(size, size));
        }

    }
    // When dir state changes to DirNone
    if(preDir != DirNone && playerDir == DirNone)
    {
        move.reverse = true;
    }
    // set state to hover until the ani is end
    if(move.reverse && nowAni->isEnd())
    {
        nowAni = &hover;
        // restore state
        move.reverse = false;
        moved = false;
    }
    //
    preDir = playerDir;
}

void Player::draw(sf::RenderTarget &target)
{
    // Entity::draw(target);
    RL_ASSERT(nowAni, "Current animation is nullptr");
    float tx = getX(), ty = getY();
    nowAni->setPosition(tx, ty);
    nowAni->draw(target);

    // Draw debug rect
    sf::RectangleShape rect(sf::Vector2f(32 * size, 48 * size));
    rect.setPosition(sf::Vector2f(tx, ty));
    rect.setFillColor(sf::Color(255, 255, 255, 0));
    rect.setOutlineColor(sf::Color(255, 0, 0));
    rect.setOutlineThickness(2);
    target.draw(rect);

    // Draw judge point
    float radius = judgePointRadius * size;
    sf::CircleShape cir(radius);
    cir.setOrigin(sf::Vector2f(radius/2, radius/2));
    cir.setPosition(getCentX(), getCentY());
    cir.setFillColor(sf::Color(255, 0, 0));
    target.draw(cir);
}

void Player::processInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            playerDir = DirUpLeft;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            playerDir = DirUpRight;
        else
            playerDir = DirUp;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            playerDir = DirDownLeft;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            playerDir = DirDownRight;
        else
            playerDir = DirDown;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        playerDir = DirRight;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        playerDir = DirLeft;
    else
    {
        playerDir = DirNone;
    }
}

void Player::processMove()
{
    RL_ASSERT(playerDir >= DirNone && playerDir < DirCount, "Invalid playerDir");
    float radAngle = Player::s_DirToAngle[playerDir] * DEG2RAD;
    // fmt::printf("%.2f\n", Player::s_MoveUnit);
    if(playerDir != DirNone)
    {
        float dis = getMovePerFrame<Player>(speed);
        x += dis * cos(radAngle);
        y += dis * sin(radAngle);
    }
}

}