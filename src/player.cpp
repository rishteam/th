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
    x = 0;
    y = 0;
    size = 2.0f;
    // Judge point collision
    judgePointX = 16 * size;
    judgePointY = 25 * size;
    judgePointRadius = 3 * size; // TODO: Check the proper radius
    // Body collision
    bodyColX = 8  * size;
    bodyColY = 5  * size;
    bodyColW = 17 * size;
    bodyColH = 43 * size;
    //
    stateChanged = false;
    // Collision
    judge.type = CollideType::Circle;
    judge.data.circle.radius = (float)judgePointRadius;

    body.type = CollideType::Rectangle;
    body.data.rectangle.width = bodyColW;
    body.data.rectangle.height = bodyColH;
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

Player::Player(float x_, float y_) : Player()
{
    x = x_;
    y = y_;
}

void Player::update()
{
    // Entity::update();
    //
    processInput();
    processMove();

    if(preDir == DirNone && playerDir != DirNone)
        stateChanged = true;
    else
        stateChanged = false;
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
    slow = false;

    // TODO(collision): Thinking more elegant way to update
    // Update colliders
    judge.data.circle.x = getCentX();
    judge.data.circle.y = getCentY();
    // body.data.rectangle.x = getX() + bodyColX;
    // body.data.rectangle.y = getY() + bodyColY;

    // TODO: dirty 64 32 768 896
    // if(x < 64) x = 64;
    // if(x > 64+768) x = 64+768;
    // if(y < 32) y = 32;
    // if(y > 32+896) y = 32+896;
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

    // Draw body collider
    sf::RectangleShape bodyRect(sf::Vector2f(bodyColW, bodyColH));
    bodyRect.setPosition(sf::Vector2f(tx+bodyColX, ty+bodyColY));
    bodyRect.setFillColor(sf::Color(255, 255, 255, 0));
    bodyRect.setOutlineColor(sf::Color(255, 0, 0));
    bodyRect.setOutlineThickness(2);
    target.draw(bodyRect);

    // Draw judge point
    float radius = judgePointRadius;
    sf::CircleShape cir(radius);
    cir.setOrigin(sf::Vector2f(radius, radius));
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

    slow = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
}

void Player::processMove()
{
    RL_ASSERT(playerDir >= DirNone && playerDir < DirCount, "Invalid playerDir");
    float radAngle = Player::s_DirToAngle[playerDir] * DEG2RAD;

    if(slow)
        speed = 0.5f;
    else
        speed = 1.0f;
    // fmt::printf("%.2f\n", Player::s_MoveUnit);
    if(playerDir != DirNone)
    {
        float dis = getMovePerFrame<Player>(speed);
        x += dis * cos(radAngle);
        y += dis * sin(radAngle);
    }
}

}