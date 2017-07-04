//
// Created by Jorge on 6/6/2017.
//

#ifndef UNTITLED_CAMERA_H
#define UNTITLED_CAMERA_H

#include "SFML/Graphics.hpp"
class Camera{
public:
    Camera(sf::IntRect viewport,sf::IntRect adjustRectangle);
    void moveCamera(sf::Vector2i);
    const sf::IntRect adjustRectangle;
    sf::IntRect getViewPort(){return viewPort;};

private:
    sf::IntRect viewPort;

};
#endif //UNTITLED_CAMERA_H
