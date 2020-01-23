#include <game.h>
#include <player.h>
#include <log.h>
#include <utils.h>

namespace rl {

std::string Player::debugPlayerDir[Player::DirCount] = {"DirNone", "DirRight", "DirUpRight", "DirUp", "DirUpLeft", "DirLeft", "DirDownLeft", "DirDown", "DirDownRight"};

float Player::s_DirToAngle[DirCount] = {-1.f, 0.f, 45.f, 90.f, 135.f, 180.f, 225.f, 270.f, 315.f};

Player::Player()
    : hover("reimu-hover", 4, "assets/player/", "reimu-hover{}.png"),
      move("reimu-move", 7, "assets/player/", "reimu-move{}.png")
{
    playerDir = preDir = DirNone;
    nowAni = &hover;
    // player attributes
    x = Game::s_WindowWidth/2;
    y = Game::s_WindowHeight/2;
    nowAni->setPosition(x, y);
    Player::s_MoveUnit = 800;
    // animation attributes
    hover.duration = 0.6f;
    hover.loop = true;
    hover.setScale(sf::Vector2f(2.f, 2.f));

    move.duration = 0.8f;
    move.reverseDuration = 0.25f;
    move.loop = false;
    move.setScale(sf::Vector2f(2.f, 2.f));
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
            move.setOrigin(sf::Vector2f(move.getLocalBound().width, 0.f));
            move.setScale(sf::Vector2f(-2.f, 2.f));
        }
        else if(isLeft(playerDir))
        {
            move.setOrigin(sf::Vector2f(0.f, 0.f));
            move.setScale(sf::Vector2f(2.f, 2.f));
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
    nowAni->setPosition(x, Game::s_WindowHeight-y); // to screen coordinate
    nowAni->draw(target);
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
    if(playerDir != DirNone)
    {
        float dis = Player::s_MoveUnit / Game::s_fps * speed;
        x += dis * cos(radAngle);
        y += dis * sin(radAngle);
        // fmt::printf("x=%.2f y=%.2f\n", x, y);
    }
}

}