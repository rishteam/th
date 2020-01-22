#pragma once

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include <fmt/core.h>

#include <core.h>

// TODO: implement load resource info for origin and fps and scale and loop

// TODO: set loop start end

// Ref: https://www.sfml-dev.org/tutorials/2.5/graphics-transform.php

namespace rl {

class Animation : public sf::Transformable
{
public:
    Animation();
    Animation(std::string texName, int count,
        std::string path, std::string fnameFmt,
        bool load=true);
    // TODO: impl
    void setInfo(std::string texName, int count,
        std::string path, std::string fnameFmt);

    void loadRes();
    void draw(sf::RenderTarget &target);

    // the duration of the animation (second)
    float duration, reverseDuration;
    bool loop;
    bool reverse;

    bool isEnd();
    sf::FloatRect getLocalBound()
    {
        if(m_spriteVec.empty()) return sf::FloatRect();
        else return m_spriteVec.back()->getLocalBounds();
    }
    void resetFrame() { m_nowFrame = 0; }
    int getNowFrame() { return m_nowFrame; }

    int getCount() { return m_count; }
private:
    // Texture attributes
    int m_count, m_nowFrame;
    std::string m_texName;
    std::string m_format, m_path;
    std::vector<std::shared_ptr<sf::Sprite>> m_spriteVec; // sprite storage
    //
    sf::Clock m_clk;
    bool ready; // impl
};

}