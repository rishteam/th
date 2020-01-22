#include <animation.h>
#include <resManager.h>
#include <log.h>

namespace rl {

// Default constructor of rl::animation
Animation::Animation()
{
    x = y = 0.f;
    scale = (sf::Vector2f){1.f, 1.f};
    fps = 10;
    m_count = m_nowFrame = 0;
    m_loop = true;
}

// TODO: sprite rotation
// Refactor: Use only one sprite but set different texture.

// Parameter Constructor of rl::Animation
// Parameters:
// std::string texName  : texture name
// int count            : Number of textures
// std::string path     : Path to the files (Need a slash`/` in the end)
// std::string fnameFmt : filename format
// bool load=true       : If true, load resources in constructor. Otherwise it need to load manaually
Animation::Animation(std::string texName, int count,
    std::string path, std::string fnameFmt,
    bool load)
    : Animation()
{
    m_texName = texName;
    m_count   = count;
    m_path    = path;
    m_format  = fnameFmt;
    if(load) loadRes();
}

void Animation::loadRes()
{
    for(int i = 0; i < m_count; i++)
    {
        std::string tar = fmt::format("{}_{}", m_texName, i);
        std::string fullPath = m_path + fmt::format(m_format, i);
        // RL_DEBUG("Loading {} path={}", tar, fullPath);
        if (!ResManager::loadRes(ResTexture, tar, fullPath))
        {
            RL_ERROR("Failed to load animation {} when loading texture {}\ntarget {}", m_texName, i, fullPath);
            m_spriteVec.clear();
            m_count = 0;
            return;
        }
        else
        {
            sf::Texture &tex = ResManager::getTexture(tar);
            m_spriteVec.push_back(std::make_shared<sf::Sprite>(tex));
            sf::Sprite &sprite = *m_spriteVec.back();
        }
    }
}

void Animation::draw(sf::RenderTarget &target)
{
    if(m_clk.getElapsedTime().asSeconds() >= 1/fps)
    {
        m_clk.restart();
        m_nowFrame++;
        if(m_nowFrame >= m_count)
        {
            if(m_loop)
                m_nowFrame = 0;
            else
                m_nowFrame = m_count-1;
        }
    }
    sf::Sprite &now = *m_spriteVec[m_nowFrame];
    now.setScale(scale);
    target.draw(now);
}

}