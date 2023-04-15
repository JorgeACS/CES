//
// Created by Jorge on 8/23/2017.
//

#ifndef UNTITLED_SOUNDMANAGER_H
#define UNTITLED_SOUNDMANAGER_H

#include "SFML/Audio.hpp"
#define MAX_SOUND
class SoundManager
{
public:
    void playSound(sf::Sound);
    void playSong(sf::Music);
    void stopSong();
    void stopSound();
    void musicIsPlaying();
    void soundIsPlaying();
private:
    sf::Music currentSong;
    sf::Sound currentSound;

};
#endif //UNTITLED_SOUNDMANAGER_H
