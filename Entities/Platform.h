//
// Created by Jorge on 6/6/2017.
//

#ifndef UNTITLED_PLATFORM_H
#define UNTITLED_PLATFORM_H

#include "SFML/Graphics.hpp"
#include "../Utilities/Point.h"
#include "../Utilities/CircularList.h"
#include "../Containers/TextureContainer.h"
class Stage;
class Platform : public sf::Drawable{
public:
    friend class Stage;
    Platform(sf::Texture *platformTexture,int type);
    Platform(int x,int y, int width, int height, std::string platformName, int repeatStyle,int type,bool dangerous = false);
    Platform(int x,int y, int width, int height, int textureWidth,int textureHeight,sf::Texture *, int repeatStyle,int type);
    void update(sf::Time );
    virtual void draw(sf::RenderTarget &,sf::RenderStates) const;
    enum platformTypes{
        still = 0
    };
    void toggleDangerous();
    enum repeatSyles{
        none = 0,
        stretchX = 1,
        stretchY = 2,
        stretchBoth = 3
    };
    bool contains(Point);
    bool isDangerous();
private:
    bool dangerous;
    sf::FloatRect collisions[4];
    Point *origin;
    Point *measurements;
    sf::Sprite sprite;
    sf::Texture platformTexture;
    int type;
};
#endif //UNTITLED_PLATFORM_H

