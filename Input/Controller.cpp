//
// Created by Jorge on 6/6/2017.
//

#include "Controller.h"
//default constructor = default scheme!
Controller::Controller(){
    this->up = sf::Keyboard::Key::Up;
    this->down = sf::Keyboard::Key::Down;
    this->left = sf::Keyboard::Key::Left;
    this->right = sf::Keyboard::Right;
    this->jump = sf::Keyboard::Key::Space;
    this->pause = sf::Keyboard::Key::Escape;
    this->run = sf::Keyboard::Key::LShift;

}

void Controller::changeInput(int button,sf::Keyboard::Key key){
    switch(button){
        case(Controller::Up):
            this->up = key;
            break;
        case(Controller::Down):
            this->down = key;
            break;
        case(Controller::Left):
            this->left = key;
            break;
        case(Controller::Right):
            this->right = key;
            break;
        case(Controller::Jump):
            this->jump = key;
            break;
        case(Controller::Pause):
            this->pause = key;
            break;
    }
};