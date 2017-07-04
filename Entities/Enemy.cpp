//
// Created by Jorge on 6/8/2017.
//

#include "Enemy.h"

Enemy::Enemy(int posX,int posY,int velX,int velY, std::string texturePath ): GameObject(posX,posY,velX,velY,texturePath){
    this->facing = -1;
    flipSprite();
}

void Enemy::update(sf::Time elapsedTime) {

    velocity->x+=speed->x;
    velocity->y+=speed->y;
    //handle y acceleration (Gravity)
    if(!grounded){
        if(this->acceleration->y < GRAVITY){
            acceleration->y+=4;
        }
    }
    velocity->y+=acceleration->y;
    this->sprite.move(velocity->x*facing, velocity->y);
    velocity->x=velocity->y =0;
    return;

}
void Enemy::flipSprite(){
    sf::FloatRect globalBounds = this->sprite.getGlobalBounds();
    sprite.setTextureRect(
            sf::IntRect(globalBounds.width, 0, -globalBounds.width, globalBounds.height)
    );
}
void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // You can draw other high-level objects
    GameObject::draw(target, states);
}