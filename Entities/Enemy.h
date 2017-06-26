//
// Created by Jorge on 6/8/2017.
//

#ifndef UNTITLED_ENEMY_H
#define UNTITLED_ENEMY_H

#include "SFML/Graphics.hpp"
#include "GameObject.h"
#define GRAVITY 15

class Enemy : public GameObject{
    friend class Stage;
public:
    Enemy(int posX,int posY,int velX,int velY,std::string);
    void update(sf::Time);
    void flipSprite();

private:
    int facing; //-1 left, 1 right
    virtual void draw(sf::RenderTarget &,sf::RenderStates) const;

};
#endif //UNTITLED_ENEMY_H
