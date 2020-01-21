#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <fmt/printf.h>

namespace rl {

#define RES_FIELD(ID) \
    static std::unordered_map<std::string, int> ID ## Idx; \
    static std::vector<std::unique_ptr<sf::ID>> ID ## Vec

#define RES_FIELD_IMPL(ID) \
    std::vector<std::unique_ptr<sf::ID>> ResManager::ID ## Vec

enum ResType
{
    ResImage,
    ResTexture,
    ResSound,
    ResMusic
};

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
    RES_FIELD(Image);
    RES_FIELD(Texture);
    RES_FIELD(Sound);
    RES_FIELD(Music);
};

}