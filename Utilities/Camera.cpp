//
// Created by Jorge on 6/6/2017.
//

#include "camera.h"

Camera::Camera(sf::IntRect viewPort,sf::IntRect aR) : adjustRectangle(aR){
    this->viewPort = viewPort;
}

void Camera::moveCamera(sf::Vector2i displacement){
    this->viewPort = {viewPort.left+displacement.x,viewPort.top+displacement.y,viewPort.width,viewPort.height};
}