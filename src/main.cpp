#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "th");
    window.setFramerateLimit(60);
    while(window.isOpen())
    {
        // Process events
        sf::Event event;
        while(window.pollEvent(event))
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
        // Update
        // Render
        window.clear();
        window.display();
    }
}