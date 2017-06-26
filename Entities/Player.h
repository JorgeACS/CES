//
// Created by Jorge on 6/5/2017.
//

#ifndef UNTITLED_PLAYER_H
#define UNTITLED_PLAYER_H

#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"
#include "../Utilities/Point.h"
#include "../Input/Controller.h"
#include "GameObject.h"
#include "../Utilities/GameStates.h"

#define MAX_V_ACCELERATION 150
#define MAX_H_ACCELERATION 50
class Stage;


class Player : public GameObject{
    friend class Stage;
public:
    Player(int posX,int posY,int velX,int velY,std::string);
    void update(sf::Time,GameState &);
    bool isAlive();

private:
    bool alive;
    int touchingWall; // 0 false, -1 left, 1 right
    bool jumpHeld;
    bool pauseHeld;
    bool fastFalling;
    float runFactor;
    Controller *controller;
    virtual void draw(sf::RenderTarget &,sf::RenderStates) const;

};
#endif //UNTITLED_PLAYER_H
