//
// Created by Jorge on 6/5/2017.
//

#include "Player.h"
Player::Player(int posX,int posY,int velX,int velY, std::string texturePath): GameObject(posX,posY,velX,velY,texturePath){
    this->controller = new Controller();
    this->runFactor = 1.0f;
    this->jumpHeld = false;
    this->touchingWall = 0;
    this->fastFalling = true;
    this->pauseHeld = false;
    this->alive = true;
}

bool Player::isAlive(){
    return this->alive;
}
void Player::update(sf::Time elapsedTime,GameState &gameState) {



    switch(gameState){
        case(GameState::Playing):{
            if(sf::Keyboard::isKeyPressed(controller->pause)){
                if(!pauseHeld){
                    gameState = GameState::Paused;
                    pauseHeld = true;
                    break;
                }

            }else{
                pauseHeld = false;
            }
            //handle y acceleration (Gravity)
            if(!grounded){
                if(this->acceleration->y < MAX_V_ACCELERATION){
                    acceleration->y+=4;
                }
            }else {
                fastFalling = false;
            }
            //handle x acceleration (walljumps)
            //gotta analyze to see if it's better to place this elsewhere
            if(acceleration->x > 0){
                acceleration->x-=10;
            }
            if(acceleration->x < 0){
                acceleration->x+=10;
            }
            //Handle running
            if(sf::Keyboard::isKeyPressed(controller->run)){
                if(grounded){
                    if(runFactor < 1.5f){
                        runFactor+=0.05f;
                    }
                    if(runFactor > 1.5f){
                        runFactor-=0.05f;
                    }
                }else{
                    if(runFactor < 2.0f){
                        runFactor+=0.05f;
                    }
                }
            }else{
                if(runFactor > 1.0f){
                    runFactor-=0.05f;
                }
            }
            //handle input to move right
            if (sf::Keyboard::isKeyPressed(controller->right)) {
                velocity->x+=speed->x;
            }
            //handle input to move left
            if (sf::Keyboard::isKeyPressed(controller->left)) {
                velocity->x-=speed->x;
            }
            //handle fast-falling
            if (sf::Keyboard::isKeyPressed(controller->down) && !grounded && !fastFalling) {
                acceleration->y = MAX_V_ACCELERATION;
                fastFalling = true;
            };
            //handle jumping
            if(sf::Keyboard::isKeyPressed(controller->jump)){
                if(!jumpHeld){
                    if(grounded){
                        if(!sf::Keyboard::isKeyPressed(controller->down)) {
                            acceleration->y = -100;//-7 == current
                            grounded = false;
                        }
                    }else{
                        //walljumping
                        if(!jumpHeld && touchingWall!=0){
                            acceleration->x=200*touchingWall;
                            acceleration->y=-100;
                            fastFalling = false;
                        }
                    }
                }

                jumpHeld = true;
            }else{
                jumpHeld = false;
            }
            //handle being able to control when you start falling during a jump
            if(!sf::Keyboard::isKeyPressed(controller->jump) && !grounded && acceleration->y < 0){
                acceleration->y = 0;
            }
            velocity->x*=runFactor;//increase speed by run acceleration
            velocity->x+= acceleration->x/10.0f;//add acceleration in x
            velocity->y+=acceleration->y/10.0f;//add acceleration in y
            velocity->x=ceil(velocity->x);//get the ceiling(make sure it stays integer)
            velocity->y=ceil(velocity->y);//get the ceiling(make sure it stays integer)
            this->sprite.move(velocity->x, velocity->y);
            velocity->x=velocity->y =0;
            GameObject::update(elapsedTime);
            break;
        }
        case(GameState::Paused):{
            if(sf::Keyboard::isKeyPressed(controller->pause)){
                if(!pauseHeld) {
                    gameState = GameState::Playing;
                    pauseHeld = true;
                }
            }else{
                pauseHeld = false;
            }
            break;
        }
    }

}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // You can draw other high-level objects
    GameObject::draw(target, states);
}