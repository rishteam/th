#include <game.h>
#include <animation.h>

#include <string>

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

}

void Game::draw()
{
    sf::RenderWindow &window = *m_window;
    static Animation ani("test", 4, "assets/player/", "reimu-hover{}.png");
    ani.scale = sf::Vector2f(5.f, 5.f);
    ani.draw(window);
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