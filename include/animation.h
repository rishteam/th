#pragma once

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include <fmt/core.h>

#include <core.h>

// TODO: implement load resource info for origin and fps and scale and loop

// Ref: https://www.sfml-dev.org/tutorials/2.5/graphics-transform.php

namespace rl {

class Animation : public sf::Transformable
{
public:
    Animation();
    Animation(std::string texName, int count,
        std::string path, std::string fnameFmt,
        bool load=true);

    void setInfo(std::string texName, int count,
        std::string path, std::string fnameFmt);

    void loadRes();
    void draw(sf::RenderTarget &target);

    float fps;

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