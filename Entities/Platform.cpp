//
// Created by Jorge on 6/6/2017.
//


#include "Platform.h"

Platform::Platform(sf::Texture *platformTexture,int type = 0){
    this->sprite.setTexture(*platformTexture);
    this->type = type;
}

Platform::Platform(int x, int y, int width, int height,std::string platformName,int repeatStyle = 0,int type = 0,bool dangerous){
    this->dangerous = dangerous;
    //this->platformTexture.loadFromFile(texturePath);
    //platformTexture.setRepeated(true);
    this->sprite.setTexture(*TextureContainer::getTexture(platformName));
    sf::FloatRect floatRect= this->sprite.getGlobalBounds();
    this->type = type;
    this->origin = new Point(x,y);
    float yScale = 1.0f,xScale = 1.0f;
    if(repeatStyle == this->stretchX){
        xScale = width/floatRect.width;
    }
    if(repeatStyle == this->stretchY){
        yScale = height/floatRect.height;
    }
    if(repeatStyle == this->stretchBoth){
        xScale = width/floatRect.width;
        yScale = height/floatRect.height;
    }
    this->measurements = new Point(width,height);
    this->sprite.setTextureRect({0,0,width/xScale,height/yScale});
    this->sprite.scale({1*xScale,1*yScale});
    this->sprite.setPosition(x,y);
}

bool Platform::isDangerous(){
    return this->dangerous;
}

Platform::Platform(int x, int y, int width, int height,int textureWidth, int textureHeight, sf::Texture *platformTexture,int repeatStyle = 0,int type = 0){
    this->sprite.setTexture(*platformTexture);
    sf::FloatRect floatRect= this->sprite.getGlobalBounds();
    this->type = type;
    this->origin = new Point(x,y);
    float yScale = 1.0f,xScale = 1.0f;
    if(repeatStyle == this->stretchX){
        xScale = width/floatRect.width;
    }
    if(repeatStyle == this->stretchY){
        yScale = height/floatRect.height;
    }
    if(repeatStyle == this->stretchBoth){
        xScale = width/floatRect.width;
        yScale = height/floatRect.height;
    }
    this->measurements = new Point(width,height);
    this->sprite.setTextureRect({0,0,width/xScale,height/yScale});
    this->sprite.scale({1*xScale,1*yScale});
    this->sprite.setPosition(x,y);
}
bool Platform::contains(Point point){
    if(point.x > origin->x && point.x < origin->x + measurements->x &&
        point.y > origin->y && point.y < origin->y +measurements->y)return true;
    return false;
}
void Platform::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // You can draw other high-level objects

    target.draw(this->sprite, states);
}