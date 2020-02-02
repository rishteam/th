#include <iostream>
#include <cstdlib>
#include <string>
#include <list>
//
#include <fmt/printf.h>
//
#include <game.h>
#include <resManager.h>

namespace rl {

// Game attributes
int Game::s_fps = 60;

// Globals
int g_WindowWidth = 1280, g_WindowHeight = 960;

float g_GameX = 64.f, g_GameY = 32.f;
float g_GameWidth = 768.f, g_GameHeight = 896.f;

Game::Game(std::string title)
    : player(416, 700),
    stage1(player)
{
    m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(g_WindowWidth, g_WindowHeight), title);
    m_window->setFramerateLimit(Game::s_fps); // fps
    // test
    ResManager::loadRes(ResTexture, "ui-background", "assets/bg.png");
    bg.setTexture(ResManager::getTexture("ui-background"));
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

BulletManager bMang;

void Game::update()
{
    sf::RenderWindow &window = *m_window;

    stage1.update();
    player.update();
}

void Game::draw()
{
    sf::RenderWindow &window = *m_window;

    player.draw(window);
    stage1.draw(window);
    window.draw(bg);
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