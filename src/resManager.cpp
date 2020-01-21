#include <exception>

#include <resManager.h>
#include <core.h>
#include <log.h>

namespace rl{

S_RES_FIELD_IMPL(Image);
S_RES_FIELD_IMPL(Texture);
S_RES_FIELD_IMPL(Sound);
std::vector<std::unique_ptr<sf::SoundBuffer>> ResManager::SoundBufferVec;
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
            sf::Image &image = *imageVec[imageIdx[name]];
            bool res = image.loadFromFile(path);
            if(!res)
            {
                RL_ERROR("Failed to load image: {} path={}", name, path);
                imageIdx.erase(name);
                imageVec.pop_back();
            }
            return res;
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
            sf::Texture &tex = *textureVec[textureIdx[name]];
            bool res = tex.loadFromFile(path);
            if (!res)
            {
                RL_ERROR("Failed to load texture: {} path={}", name, path);
                textureIdx.erase(name);
                textureVec.pop_back();
            }
            return res;
        }
    }
    break;

    case ResSound:
    case ResMusic:
    {
        if (path.find(".wav") == std::string::npos &&
            path.find(".ogg") == std::string::npos &&
            path.find(".flag") == std::string::npos)
        {
            RL_WARN("Wrong extention for sound file");
            return false;
        }

        if(type == ResSound)
        {
            auto &soundVec = ResManager::SoundVec;
            auto &soundBufVec = ResManager::SoundBufferVec;
            auto &soundIdx = ResManager::SoundIdx;
            if(!soundIdx.count(name))
            {
                soundIdx[name] = soundVec.size();
                soundVec.push_back(std::make_unique<sf::Sound>());
                soundBufVec.push_back(std::make_unique<sf::SoundBuffer>());
            }
            int idx = soundIdx[name];
            sf::SoundBuffer &soundBuf = *soundBufVec[idx];
            sf::Sound &sound = *soundVec[idx];

            bool res = soundBuf.loadFromFile(path);
            if (!res)
            {
                RL_ERROR("Failed to load sound: {} path={}", name, path);
                soundVec.pop_back();
                soundBufVec.pop_back();
                soundIdx.erase(name);
            }
            else
                sound.setBuffer(soundBuf);
            return res;
        }
        else if(type == ResMusic)
        {
            auto &musicIdx = ResManager::MusicIdx;
            auto &musicVec = ResManager::MusicVec;
            if (!musicIdx.count(name))
            {
                musicIdx[name] = musicVec.size();
                musicVec.push_back(std::make_unique<sf::Music>());
            }
            int idx = musicIdx[name];
            sf::Music &music = *musicVec[idx];
            bool res = music.openFromFile(path);
            if(!res)
            {
                RL_ERROR("Failed to load music: {} path={}", name, path);
                musicVec.pop_back();
                musicIdx.erase(name);
            }
            return idx;
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
    auto &soundIdx = ResManager::SoundIdx;
    auto &soundVec = ResManager::SoundVec;
    RL_ASSERT(soundIdx.count(name), "Sound {} not found", name);
    return *soundVec[soundIdx[name]];
}

sf::Music& ResManager::getMusic(std::string name)
{
    auto &musicIdx = ResManager::MusicIdx;
    auto &musicVec = ResManager::MusicVec;
    RL_ASSERT(musicIdx.count(name), "Music {} not found", name);
    return *musicVec[musicIdx[name]];
}

}
