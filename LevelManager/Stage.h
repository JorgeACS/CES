//
// Created by Jorge on 6/6/2017.
//

#ifndef UNTITLED_STAGE_H
#define UNTITLED_STAGE_H

#include "SFML/Graphics.hpp"
#include "../Entities/Platform.h"
#include "../Entities/Player.h"
#include "../Entities/Enemy.h"
#include "../Utilities/GameStates.h"
#include "../Containers/TextureContainer.h"
#include <vector>
#include <math.h>
#include <string.h>

#define FLOOR 0
#define LEFT_WALL 1
#define RIGHT_WALL 2
#define CEILING 3

class Stage : public sf::Drawable {
public:
    Stage(int width,int height,std::string,Player *,int repeatStyle);
    void update(sf::Time,sf::View*,sf::RenderWindow*,GameState &);
    void addPlatform(int x, int y, int width, int height,
                     std::string , int repeatStyle = 0, int style = 0,bool dangerous =false);
    void checkPlayerCollisions(sf::Time);
    void checkEnemyCollisions(sf::Time);
    bool toggleDebug(){debug=!debug;};
    void setOrigin(sf::Vector2i);
    void addEnemy(int xPos, int yPos, int xVel, int yVel, std::string);
    enum repeatStyles{
        none = 0,
        stretchX = 1,
        stretchY = 2,
        stretchBoth = 3
    };
private:
    sf::Vector2i origin;
    std::vector<sf::RectangleShape> collisions;
    Player *player;
    sf::Texture backgroundTexture;
    bool debug;
    std::vector<Platform*> platforms;
    std::vector<Enemy*> enemies;
    sf::Sprite background;
    virtual void draw(sf::RenderTarget &,sf::RenderStates) const;

};
#endif //UNTITLED_STAGE_H
