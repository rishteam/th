#include <string>
//
#include <fmt/printf.h>
//
#include <game.h>

namespace rl {

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

void Game::update()
{
    player.update();
}

void Game::draw()
{
    sf::RenderWindow &window = *m_window;
    // static Animation ani("test", 7, "assets/player/", "reimu-move{}.png");
    // ani.duration = 0.9f;
    // static float angle = 0.f;
    // angle += 0.001f;
    // static float radius = 50.f;
    // ani.setScale(sf::Vector2f(5.f, 5.f));
    // ani.setPosition(600 + radius * cos(angle * DEG2RAD),
    //     400 + radius * sin(angle * DEG2RAD));
    // ani.rotate(0.1f);
    // ani.draw(window);

    player.draw(window);
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