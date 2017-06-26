//
// Created by Jorge on 6/19/2017.
//

#ifndef UNTITLED_TEXTURECONTAINER_H
#define UNTITLED_TEXTURECONTAINER_H
#include <unordered_map>
#include <string>
#include "SFML/Graphics.hpp"
class TextureContainer{
public:
    static sf::Texture* addTexture(std::string textureName, std::string texturePath,bool repeated = false);
    static sf::Texture* getTexture(std::string textureName);
private:
    static std::unordered_map<std::string,sf::Texture> textures;
    static int textureCount;
};
#endif //UNTITLED_TEXTURECONTAINER_H
