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

}

void Game::draw()
{

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