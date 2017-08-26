//
// Created by Jorge on 8/23/2017.
//

#ifndef UNTITLED_SOUNDBUFFERCONTAINER_H
#define UNTITLED_SOUNDBUFFERCONTAINER_H

#include <iostream>
#include "SFML/Audio.hpp"

#include <unordered_map>
#include <string>
#include "SFML/Graphics.hpp"
class SoundBufferContainer{
public:
    static sf::SoundBuffer* addSoundBuffer(std::string soundBufferName, std::string soundBufferPath);
    static sf::SoundBuffer* getSoundBuffer(std::string soundBufferName);
private:
    static std::unordered_map<std::string,sf::SoundBuffer> soundBuffers;
    static int soundBufferCount;
};

#endif //UNTITLED_SOUNDBUFFERCONTAINER_H
