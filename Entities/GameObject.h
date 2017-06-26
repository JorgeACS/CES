//
// Created by Jorge on 6/8/2017.
//

#ifndef UNTITLED_GAMEOBJECT_H
#define UNTITLED_GAMEOBJECT_H


#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"
#include "../Utilities/Point.h"
#include "../Input/Controller.h"
#include "../Containers/TextureContainer.h"

class Stage;

#define LEFT -1
#define RIGHT 1
class GameObject : public sf::Drawable{
    friend class Stage;
public:
    GameObject(int posX,int posY,int velX,int velY,std::string);
    virtual void update(sf::Time);

protected:
    sf::Vector2f localCollisionPoint;
    sf::Vector2f *acceleration;
    sf::Vector2f *speed;
    sf::Vector2f *velocity;
    sf::Texture* objectTexture;
    bool grounded;
    sf::Sprite sprite;
    virtual void draw(sf::RenderTarget &,sf::RenderStates) const;

};


#endif //UNTITLED_GAMEOBJECT_H
