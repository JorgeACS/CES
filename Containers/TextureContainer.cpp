//
// Created by Jorge on 6/19/2017.
//

#include "TextureContainer.h"
#include <iostream>

std::unordered_map<std::string,sf::Texture> TextureContainer::textures;
int TextureContainer::textureCount = 0;
sf::Texture * TextureContainer::addTexture(std::string textureName,std::string texturePath,bool repeated){
    if(textures[textureName].getSize().x != 0){
        std::cout << "Texture already there" << std::endl;

    }else{
        textures[textureName].loadFromFile("./../"+texturePath);
        std::cout << "added texture " << textureName << std::endl;
        textureCount++;
    }
    textures[textureName].setRepeated(repeated);
    return &textures[textureName];
}

 sf::Texture* TextureContainer::getTexture(std::string textureName){
    return &textures[textureName];
}