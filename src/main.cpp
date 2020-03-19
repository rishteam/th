#include <functional>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <fmt/printf.h>

#include <game.h>

using namespace rl;

int main()
{
    Game game("th");
    game.run();
}