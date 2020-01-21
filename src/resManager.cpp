#include <exception>

#include <resManager.h>
#include <core.h>
#include <log.h>

namespace rl{

S_RES_FIELD_IMPL(Image);
S_RES_FIELD_IMPL(Texture);
S_RES_FIELD_IMPL(Sound);
S_RES_FIELD_IMPL(Music);

bool ResManager::loadRes(ResType type, std::string name, std::string path)
{
    switch(type)
    {
    case ResImage:
    case ResTexture:
    {
        if(path.find(".png") == std::string::npos &&
           path.find(".jpg") == std::string::npos)
        {
            RL_WARN("Wrong extention for image file");
            return false;
        }

        if(type == ResImage)
        {
            auto & imageIdx = ResManager::ImageIdx;
            auto & imageVec = ResManager::ImageVec;
            if (!imageIdx.count(name))
            {
                imageIdx[name] = imageVec.size();
                imageVec.push_back(std::make_unique<sf::Image>());
            }
            auto &image = *imageVec[imageIdx[name]];
            return image.loadFromFile(path);
        }
        else if(type == ResTexture)
        {
            auto &textureIdx = ResManager::TextureIdx;
            auto &textureVec = ResManager::TextureVec;
            if (!textureIdx.count(name))
            {
                textureIdx[name] = textureVec.size();
                textureVec.push_back(std::make_unique<sf::Texture>());
            }
            auto &tex = *textureVec[textureIdx[name]];
            RL_DEBUG("{} {}", name, path);
            return tex.loadFromFile(path);
        }
    }
    break;

    default:
    break;
    }
    return false;
}

sf::Image& ResManager::getImage(std::string name)
{
    auto &imageIdx = ResManager::ImageIdx;
    auto &imageVec = ResManager::ImageVec;
    RL_ASSERT(imageIdx.count(name), "Image {} not found", name);
    return *imageVec[imageIdx[name]];
}

sf::Texture& ResManager::getTexture(std::string name)
{
    auto &texIdx = ResManager::TextureIdx;
    auto &texVec = ResManager::TextureVec;
    RL_ASSERT(texIdx.count(name), "Texture {} not found", name);
    return *texVec[texIdx[name]];
}

sf::Sound& ResManager::getSound(std::string name)
{
}

sf::Music& ResManager::getMusic(std::string name)
{
}

}
