#include <game.h>
#include <animation.h>
#include <utils.h>

#include <string>

#include <fmt/printf.h>

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
    static float angle = 0.f;
    angle += 0.001f;
    static float radius = 50.f;
    ani.scale = sf::Vector2f(5.f, 5.f);
    ani.x = 600 + radius * cos(angle * DEG2RAD);
    ani.y = 400 + radius * sin(angle * DEG2RAD);
    ani.rotate += 0.1f;
    // fmt::printf("angle = %.2f\n", ani.rotate);
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