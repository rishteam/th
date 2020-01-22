#pragma once

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include <fmt/core.h>

namespace rl {

class Animation
{
public:
    Animation();
    Animation(std::string texName, int count, std::string path, std::string fnameFmt, bool load=true);
    // Animation(const Animation &ani);
    // Animation& operator=(const Animation& rhs);

    void loadRes();
    void draw(sf::RenderTarget &target);

    float fps;
    float x, y;
    sf::Vector2f scale;
private:
    // Texture attributes
    bool m_loop = false;
    int m_count, m_nowFrame;
    std::string m_texName;
    std::string m_format, m_path;
    std::vector<std::shared_ptr<sf::Sprite>> m_spriteVec; // sprite storage
    //
    sf::Clock m_clk;
    bool ready; // impl
};

}