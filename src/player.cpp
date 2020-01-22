#include <player.h>
#include <log.h>

namespace rl {

std::string Player::debugPlayerDir[Player::DirCount] = {"DirNone", "DirRight", "DirUpRight", "DirUp", "DirUpLeft", "DirLeft", "DirDownLeft", "DirDown", "DirDownRight"};

Player::Player()
    : hover("reimu-hover", 4, "assets/player/", "reimu-hover{}.png"),
      move("reimu-move", 7, "assets/player/", "reimu-move{}.png")
{
    playerDir = preDir = DirNone;
    nowAni = nullptr;
    // ani settings
    hover.duration = 0.6f;
    hover.loop = true;
    hover.setScale(sf::Vector2f(3.f, 3.f));

    move.duration = 0.8f;
    move.reverseDuration = 0.5f;
    move.loop = false;
    move.setScale(sf::Vector2f(3.f, 3.f));
}

void Player::update()
{
    // Entity::update();
    //
    processInput();
    //
    static bool moved = false;

    fmt::print("{} {}\n", Player::debugPlayerDir[preDir], Player::debugPlayerDir[playerDir]);

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
            move.setScale(sf::Vector2f(-3.f, 3.f));
        }
        else if(isLeft(playerDir))
        {
            move.setOrigin(sf::Vector2f(0.f, 0.f));
            move.setScale(sf::Vector2f(3.f, 3.f));
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

}