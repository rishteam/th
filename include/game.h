#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include <player.h>
#include <bullet.h>
#include <animation.h>
#include <utils.h>

namespace rl {

class Game
{
public:
    static int s_fps;
    static int s_WindowWidth, s_WindowHeight;

    Game(std::string title);
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

    sf::RectangleShape bg;

    Player player;
};

}