//
// Created by Jorge on 6/6/2017.
//

#ifndef UNTITLED_CONTROLLER_H
#define UNTITLED_CONTROLLER_H
#include "SFML/Window.hpp"
//#include "../Entities/Player.h"
class Controller{
    friend class Player;
public:
    Controller();
    void changeInput(int,sf::Keyboard::Key);
    enum Inputs{
        Up =1,
        Down = 2,
        Left =3,
        Right =4,
        Jump =5,
        Run  =6,
        Pause =7
    };
private:
    sf::Keyboard::Key lastKeyPressed;
    sf::Keyboard::Key up;
    sf::Keyboard::Key down;
    sf::Keyboard::Key left;
    sf::Keyboard::Key right;
    sf::Keyboard::Key jump;
    sf::Keyboard::Key pause;
    sf::Keyboard::Key run;


};
#endif //UNTITLED_CONTROLLER_H
