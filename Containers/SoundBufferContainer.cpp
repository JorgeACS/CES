//
// Created by Jorge on 8/23/2017.
//

#include "SoundBufferContainer.h"

std::unordered_map<std::string,sf::SoundBuffer> SoundBufferContainer::soundBuffers;
int SoundBufferContainer::soundBufferCount = 0;
sf::SoundBuffer * SoundBufferContainer::addSoundBuffer(std::string soundBufferName,std::string soundBufferPath){
    if(soundBuffers[soundBufferName].getDuration() != sf::Time::Zero){
        std::cout << "Sound buffer already there" << std::endl;

    }else{
        soundBuffers[soundBufferName].loadFromFile(soundBufferPath);
        std::cout << "added sound buffer " << soundBufferName << std::endl;
        soundBufferCount++;
    }
    return &soundBuffers[soundBufferName];
}

sf::SoundBuffer* SoundBufferContainer::getSoundBuffer(std::string soundBufferName){
    return &soundBuffers[soundBufferName];
}