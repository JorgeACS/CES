//
// Created by Jorge on 6/6/2017.
//


#include "Platform.h"

#define PLAYER_X_POINT 32
#define PLAYER_Y_POINT 64

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

    if(this->type == 0 ){

        sf::FloatRect platformRect = sprite.getGlobalBounds();
        //floor detection

        collisions[0] = {platformRect.left-5,platformRect.top,platformRect.width+10,20};
        //el offset de -5 y +5 es para que la accion de caminar fuera de una plataforma
        //se sienta mas natural para el jugador.. esta pensado especificamente en la base del sprite
        //usado actualmente (la punta del corazon)
        collisions[1] = {
                platformRect.left-PLAYER_X_POINT,
                platformRect.top+10,
                PLAYER_X_POINT,
                platformRect.height+PLAYER_Y_POINT-10
        };
        collisions[2] = {
                platformRect.left+platformRect.width,
                platformRect.top+10, //+1 so you don't collision a wall if you're standing on its corresp. ceiling
                PLAYER_X_POINT,
                platformRect.height+PLAYER_Y_POINT-10

        };
        collisions[3] ={
                platformRect.left,
                platformRect.top+platformRect.height,
                platformRect.width,
                PLAYER_Y_POINT
        };
    }
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