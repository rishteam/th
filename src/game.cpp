#include <string>
#include <list>
//
#include <fmt/printf.h>
//
#include <game.h>

namespace rl {

int Game::s_fps = 60;

int Game::s_WindowWidth = 1280, Game::s_WindowHeight = 960;

Game::Game(std::string title)
{
    m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(Game::s_WindowWidth, Game::s_WindowHeight), title);
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
        processEvent();
        update();
        window.clear();
        draw();
        window.display();
    }
}

std::list<Bullet> validBullets;
sf::Clock testClk;

void Game::update()
{
    sf::RenderWindow &window = *m_window;
    // TEST -------------------------------------
    auto mPos = sf::Mouse::getPosition(window);

    for(int i = 0; i < 100; i++)
    {
        validBullets.push_back(Bullet(mPos.x, mPos.y));
        Bullet &b = validBullets.back();
        b.dir = rand() % 360;
    }
    for(auto it = validBullets.begin(); it != validBullets.end();)
    {
        it->update();
        if(it->x <= -5 || it->x >= Game::s_WindowWidth+5 || it->y <= -5 || it->y >= Game::s_WindowHeight+5)
        {
            validBullets.erase(it++);
        }
        else
            it++;
    }
    //
    player.update();
}

void Game::draw()
{
    sf::RenderWindow &window = *m_window;

    window.draw(bg);
    player.draw(window);

    for(auto &i : validBullets)
        i.draw(window);
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