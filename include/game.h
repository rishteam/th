#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include <player.h>
#include <bullet.h>
#include <stage.h>
#include <animation.h>
#include <utils.h>

namespace rl {

class Game
{
public:
    static int s_fps;

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

    sf::Sprite bg;

    Player player;
    Stage1 stage1;
};

template <typename T>
float getMovePerFrame(float speed)
{
    return (T::s_MoveUnit * speed) / Game::s_fps;
}

extern int g_WindowWidth, g_WindowHeight;
extern float g_GameX, g_GameY;
extern float g_GameWidth, g_GameHeight;
}