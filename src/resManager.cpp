#include <resManager.h>
#include <log.h>

namespace rl{

RES_FIELD_IMPL(Image);
RES_FIELD_IMPL(Texture);
RES_FIELD_IMPL(Sound);
RES_FIELD_IMPL(Music);

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
            WARN("Wrong ext for file");
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
}

sf::Texture& ResManager::getTexture(std::string name)
{
}

sf::Sound& ResManager::getSound(std::string name)
{
}

sf::Music& ResManager::getMusic(std::string name)
{
}

}
