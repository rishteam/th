#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include <animation.h>
#include <utils.h>
#include <player.h>

namespace rl {

class Game
{
public:
    Game(std::string title)
    {
        m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1920, 1080), title);
        m_window->setFramerateLimit(60); // fps
    }
    // Run the game
    // executing the game loop
    void run();

    // Process events
    void processEvent();

    // Update the game
    void update();

    // Draw on the window
    void draw();

private:
    std::unique_ptr<sf::RenderWindow> m_window;

    Player player;
};

}