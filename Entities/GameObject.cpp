//
// Created by Jorge on 6/8/2017.
//


//
// Created by Jorge on 6/5/2017.
//

#include "GameObject.h"

GameObject::GameObject(int posX,int posY,int velX,int velY, std::string textureName){
    this->objectTexture = TextureContainer::getTexture(textureName);
    this->speed = new sf::Vector2f(velX,velY);
    this->velocity = new sf::Vector2f(velX,velY);
    this->acceleration = new sf::Vector2f(0.0f,0.0f);
    this->sprite.setTexture(*objectTexture);
    //you should change this to be able to set player size dynamically
    sf::FloatRect bounds = this->sprite.getLocalBounds();
    this->localCollisionPoint = {(bounds.left+bounds.width)/2,bounds.top+bounds.height};
    this->sprite.setPosition(posX,posY);
    this->grounded = false;
}

void GameObject::update(sf::Time elapsedTime) {
    this->sprite.move(velocity->x, velocity->y);
    velocity->x=velocity->y =0;
    return;

}

void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // You can draw other high-level objects
    target.draw(this->sprite, states);
}