#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <fmt/printf.h>

namespace rl {

// static
#define S_RES_FIELD(ID)                                    \
    static std::unordered_map<std::string, int> ID ## Idx; \
    static std::vector<std::unique_ptr<sf::ID>> ID ## Vec

#define S_RES_FIELD_IMPL(ID)                                  \
    std::unordered_map<std::string, int> ResManager::ID ## Idx; \
    std::vector<std::unique_ptr<sf::ID>> ResManager::ID ## Vec

enum ResType
{
    ResImage,
    ResTexture,
    ResSound,
    ResMusic
};

// Usage: e.g. load a texture (namesapce rl)
// ResManager::loadRes(ResTexture, "test", "/path/to/test.png");
//
// with copy and readonly
// sf::Texture tex = ResManager::getTexture("test");
//
// without copy and RW
// sf::Texture &tex = ResManager::getTexture("test");
//
// without copy and readonly
// const sf::Texture &tex = ResManager::getTexture("test");

// Resource Manager
class ResManager
{
public:
    static bool loadRes(ResType type, std::string name, std::string path);

    // throw exceptions
    static sf::Image& getImage(std::string name);
    static sf::Texture& getTexture(std::string name);
    static sf::Sound& getSound(std::string name);
    static sf::Music& getMusic(std::string name);

private:
    S_RES_FIELD(Image);
    S_RES_FIELD(Texture);
    S_RES_FIELD(Sound);
    S_RES_FIELD(Music);
};

}