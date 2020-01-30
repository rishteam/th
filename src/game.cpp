#include <iostream>
#include <cstdlib>
#include <string>
#include <list>
//
#include <fmt/printf.h>
//
#include <game.h>

namespace rl {

// Game attributes
int Game::s_fps = 60;
int g_WindowWidth = 1280, g_WindowHeight = 960;

Game::Game(std::string title)
{
    m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(g_WindowWidth, g_WindowHeight), title);
    m_window->setFramerateLimit(Game::s_fps); // fps
    // test
    bg.setPosition(sf::Vector2f(64.f, 32.f));
    bg.setSize(sf::Vector2f(768, 896));
    bg.setFillColor(sf::Color(255, 255, 255));
}

void Game::run()
{
    sf::RenderWindow &window = *m_window;
    while (window.isOpen())
    {
        system("clear");
        processEvent();
        update();
        window.clear();
        draw();
        window.display();
    }
}

BulletManager bMang;
Bullet b(Bullet::BulletType::Disappear, Bullet::BulletShotByType::NPCnormal,
        0, 0, 1.f, 0);
Bullet c(Bullet::BulletType::Disappear, Bullet::BulletShotByType::NPCnormal,
         0, 0, 1.f, 0);

void Game::update()
{
    sf::RenderWindow &window = *m_window;
    // TEST -------------------------------------
    auto mPos = sf::Mouse::getPosition(window);

    fmt::printf("%d %d\n", mPos.x, g_WindowHeight - mPos.y);

    // for(int i = 0; i < 5; i++)
    // {
    //     bMang.addBullet(Bullet::BulletType::Disappear, Bullet::BulletShotByType::NPCspecial, mPos.x, mPos.y, 1.f, rand() % 360);
    // }
    // bMang.update();

    static float off = 0;
    b.update(100, 150);
    c.update(100, 150 + off);
    if(player.stateChanged)
    {
        off += 1.f;
    }
    //
    // player.x = 170;
    // player.y = 150;
    player.update();

    // bMang.collideWith(player);
    if(b.isCollideWith(c))
    {
        RL_DEBUG("Collide");
    }
    else
    {
        RL_DEBUG("not");
    }
}

void Game::draw()
{
    sf::RenderWindow &window = *m_window;

    window.draw(bg);
    // player.draw(window);
    b.draw(window);
    c.draw(window);
    // bMang.draw(window);
}

void Game::processEvent()
{
    sf::RenderWindow &window = *m_window;
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        default:
            break;
        }
    }
}

}