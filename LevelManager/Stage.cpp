//
// Created by Jorge on 6/6/2017.
//


#include "Stage.h"
#include <array>

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800
Stage::Stage(int width, int height,std::string texturePath,Player *player,int repeatStyle = 0){
    this->backgroundTexture.loadFromFile(texturePath);
    this->backgroundTexture.setRepeated(true);
    this->background.setTexture(backgroundTexture);
    sf::FloatRect floatRect = this->background.getGlobalBounds();
    float yScale = 1.0f,xScale = 1.0f;
    this->background.setTextureRect({0,0,width/xScale,height/yScale});
    this->background.move(-500,0);
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

    this->background.scale({1*xScale,1*yScale});
    this->debug = true;


    this->player = player;
    this->origin = {0,0};


}

void Stage::setOrigin(sf::Vector2i origin){
    this->origin = origin;
}
void Stage::addPlatform(int x, int y, int width, int height,
                        std::string texturePath, int repeatStyle, int type,bool dangerous)
{
    Platform *newPlatform = new Platform(x,y,width,height,texturePath,repeatStyle,type,dangerous);
    this->platforms.push_back(newPlatform);

}

void Stage::addEnemy(int xPos, int yPos, int xVel, int yVel,std::string texturePath){
    Enemy *newEnemy = new Enemy(xPos,yPos,xVel,yVel,texturePath);
    this->enemies.push_back(newEnemy);

}

void Stage::checkPlayerCollisions(sf::Time elapsedTime){
    sf::FloatRect playerRect = player->sprite.getGlobalBounds();
    std::vector<Platform*>::iterator pit = platforms.begin();
    bool platformIntersected = false;
    bool wallTouched = false;
    sf::RectangleShape collision;
    collision.setOutlineThickness(2);
    collision.setFillColor(sf::Color::Transparent);
    this->collisions.clear();//clear previous debug collisions
    while(pit!=platforms.end()){

        sf::FloatRect platformRect = (*pit)->sprite.getGlobalBounds();
        //floor detection
        int platformType = (*pit)->type;//we'll use this to update the collisions of moving platforms

        sf::FloatRect floorRect =  (*pit)->collisions[FLOOR];
        if(debug){
            collision.setSize(sf::Vector2f(floorRect.width,floorRect.height));
            collision.setPosition({floorRect.left,floorRect.top});
            collision.setOutlineColor((sf::Color::Green));
            this->collisions.push_back(collision);
        }


        sf::Vector2f playerCollision =
                {playerRect.left+player->localCollisionPoint.x,
                 playerRect.top+player->localCollisionPoint.y};
        if(floorRect.contains(playerCollision)){
            platformIntersected = true;
            float offSet = (playerRect.top + playerRect.height) - (floorRect.top);
            player->sprite.move(0,-offSet);
            player->grounded = true;
            player->acceleration->x = 0;
            player->acceleration->y=0;
            playerRect = player->sprite.getGlobalBounds();
            playerCollision =
                    {playerCollision.x,
                     playerRect.top+player->localCollisionPoint.y};
        }

        //-----//left wall
        sf::FloatRect leftWallRect = (*pit)->collisions[LEFT_WALL];
        if(debug){
            collision.setSize(sf::Vector2f(leftWallRect.width,leftWallRect.height));
            collision.setPosition({leftWallRect.left,leftWallRect.top});
            collision.setOutlineColor((sf::Color::Blue));
            this->collisions.push_back(collision);
        }

        if(leftWallRect.contains(playerCollision)){
            player->touchingWall = -1;

            wallTouched = true;
            float offSet = (playerRect.left + player->localCollisionPoint.x) - (leftWallRect.left);
            player->sprite.move(-offSet,0);
            playerRect = player->sprite.getGlobalBounds();
            playerCollision =
                    {playerRect.left+player->localCollisionPoint.x,
                     playerRect.top+player->localCollisionPoint.y};
        }

        //right wall

        sf::FloatRect rightWallRect = (*pit)->collisions[RIGHT_WALL];


        collision.setSize(sf::Vector2f(rightWallRect.width,rightWallRect.height));
        collision.setPosition({rightWallRect.left,rightWallRect.top});
        collision.setOutlineColor((sf::Color::Blue));
        this->collisions.push_back(collision);
        if(rightWallRect.contains(playerCollision)){
            player->touchingWall = 1;
            wallTouched = true;
            float offSet = (rightWallRect.left+rightWallRect.width)-playerCollision.x;
            player->sprite.move(offSet-1,0);
            playerRect = player->sprite.getGlobalBounds();
            playerCollision =
                    {playerRect.left+player->localCollisionPoint.x,
                     playerRect.top+player->localCollisionPoint.y};
        }

        sf::FloatRect ceilingRect = (*pit)->collisions[CEILING];
        if(debug){
            collision.setSize(sf::Vector2f(ceilingRect.width,ceilingRect.height));
            collision.setPosition({ceilingRect.left,ceilingRect.top});
            collision.setOutlineColor((sf::Color::Red));
            this->collisions.push_back(collision);
        }


        if(player->acceleration->y >0){
            pit++;
            continue;
        }
        //Ceiling detection

        if(ceilingRect.contains(playerCollision)){
            float offSet = (ceilingRect.top+ceilingRect.height)-playerCollision.y;
            player->sprite.move(0,offSet);
            player->acceleration->y=0;
        }
        pit++;//advancing platform iterator
    }

    if(!platformIntersected){
        player->grounded = false;
    }
    if(!wallTouched){
        player->touchingWall = 0;
    }
}

void Stage::checkEnemyCollisions(sf::Time elapsedTime){
    std::vector<Enemy*>::iterator eit = enemies.begin();
    while(eit != enemies.end()){
        (*eit)->update(elapsedTime);
        sf::FloatRect enemyRect = (*eit)->sprite.getGlobalBounds();
        std::vector<Platform*>::iterator pit = platforms.begin();
        bool platformIntersected = false;
        while(pit!=platforms.end()){
            sf::FloatRect platformRect = (*pit)->sprite.getGlobalBounds();
            //floor detection

            sf::FloatRect floorRect = {platformRect.left,platformRect.top,platformRect.width,20};
            sf::Vector2f enemyCollision =
                    {enemyRect.left+(*eit)->localCollisionPoint.x,
                     enemyRect.top+(*eit)->localCollisionPoint.y};
            if(floorRect.contains(enemyCollision)){
                platformIntersected = true;
                float offSet = (enemyRect.top + enemyRect.height) - (floorRect.top);
                (*eit)->sprite.move(0,-offSet);
                (*eit)->grounded = true;
                (*eit)->acceleration->y=0;
                enemyRect = (*eit)->sprite.getGlobalBounds();
                enemyCollision =
                        {enemyRect.left+(*eit)->localCollisionPoint.x,
                         enemyRect.top+(*eit)->localCollisionPoint.y};
            }

            //-----//left wall
            sf::FloatRect leftWallRect = {
                    platformRect.left-(*eit)->localCollisionPoint.x,
                    platformRect.top+5,
                    (*eit)->localCollisionPoint.x*2,
                    platformRect.height+(*eit)->localCollisionPoint.y
            };
            if(leftWallRect.contains(enemyCollision)){

                (*eit)->facing = LEFT;
                (*eit)->sprite.setTextureRect(
                        sf::IntRect(enemyRect.width, 0, -enemyRect.width, enemyRect.height)
                );
                float offSet = (enemyRect.left + (*eit)->localCollisionPoint.x) - (leftWallRect.left);
                //adjust the enemy to be position next to the wall
                (*eit)->sprite.move(-offSet,0);
                enemyRect = (*eit)->sprite.getGlobalBounds();
                enemyCollision =
                        {enemyRect.left+(*eit)->localCollisionPoint.x,
                         enemyRect.top+(*eit)->localCollisionPoint.y};
            }

            //right wall

            sf::FloatRect rightWallRect = {
                    platformRect.left+platformRect.width,
                    platformRect.top+5, //+1 so you don't collision a wall if you're standing on it
                    (*eit)->localCollisionPoint.x,
                    platformRect.height+(*eit)->localCollisionPoint.y

            };
            if(rightWallRect.contains(enemyCollision)){
                (*eit)->facing = RIGHT;
                (*eit)->sprite.setTextureRect(sf::IntRect(0, 0, enemyRect.width, enemyRect.height));
                float offSet = (rightWallRect.left+rightWallRect.width)-enemyCollision.x;
                //adjust the enemy to be position next to the wall
                (*eit)->sprite.move(offSet,0);
                enemyRect = (*eit)->sprite.getGlobalBounds();
                enemyCollision =
                        {enemyRect.left+(*eit)->localCollisionPoint.x,
                         enemyRect.top+(*eit)->localCollisionPoint.y};
            }
            if((*eit)->acceleration->y >0){
                pit++;
                continue;
            }
            //Ceiling detection
            sf::FloatRect ceilingRect = {
                    platformRect.left-(*eit)->localCollisionPoint.x+1,//makes sure you don't hit a ceiling
                    //after being displaced by a wall
                    platformRect.top+platformRect.height,
                    platformRect.width+(*eit)->localCollisionPoint.x,
                    (*eit)->localCollisionPoint.y
            };
            if(ceilingRect.contains(enemyCollision)){
                float offSet = (ceilingRect.top+ceilingRect.height)-enemyCollision.y;
                (*eit)->sprite.move(0,offSet);
                (*eit)->acceleration->y=0;
            }
            pit++;
        }
        if(!platformIntersected){
            (*eit)->grounded = false;
        }
        eit++;
    }
}

std::array<bool,4> Stage::checkEntityCollisions(sf::Time elapsedTime,GameObject entity){

        std::array<bool,4> entityCollisions{false,false,false,false};
        entity.update(elapsedTime);
        sf::FloatRect enemyRect = entity.sprite.getGlobalBounds();
        std::vector<Platform*>::iterator pit = platforms.begin();
        bool platformIntersected = false;
        while(pit!=platforms.end()){
            sf::FloatRect platformRect = (*pit)->sprite.getGlobalBounds();

            std::array<int,4>::iterator cit = entityCollisions.begin();
            //floor detection
            sf::FloatRect floorRect = {platformRect.left,platformRect.top,platformRect.width,20};
            sf::Vector2f enemyCollision =
                    {enemyRect.left+entity.localCollisionPoint.x,
                     enemyRect.top+entity.localCollisionPoint.y};
            if(floorRect.contains(enemyCollision)){
                platformIntersected = true;
                float offSet = (enemyRect.top + enemyRect.height) - (floorRect.top);
                entity.sprite.move(0,-offSet);
                entity.grounded = true;
                entity.acceleration->y=0;
                enemyRect = entity.sprite.getGlobalBounds();
                enemyCollision =
                        {enemyRect.left+entity.localCollisionPoint.x,
                         enemyRect.top+entity.localCollisionPoint.y};
            }

            //-----//left wall
            sf::FloatRect leftWallRect = {
                    platformRect.left-entity.localCollisionPoint.x,
                    platformRect.top+5,
                    entity.localCollisionPoint.x*2,
                    platformRect.height+entity.localCollisionPoint.y
            };
            if(leftWallRect.contains(enemyCollision)){

                entity.facing = LEFT;
                entity.sprite.setTextureRect(
                        sf::IntRect(enemyRect.width, 0, -enemyRect.width, enemyRect.height)
                );
                float offSet = (enemyRect.left + entity.localCollisionPoint.x) - (leftWallRect.left);
                //adjust the enemy to be position next to the wall
                entity.sprite.move(-offSet,0);
                enemyRect = entity.sprite.getGlobalBounds();
                enemyCollision =
                        {enemyRect.left+entity.localCollisionPoint.x,
                         enemyRect.top+entity.localCollisionPoint.y};
            }

            //right wall

            sf::FloatRect rightWallRect = {
                    platformRect.left+platformRect.width,
                    platformRect.top+5, //+1 so you don't collision a wall if you're standing on it
                    entity.localCollisionPoint.x,
                    platformRect.height+entity.localCollisionPoint.y

            };
            if(rightWallRect.contains(enemyCollision)){
                entity.facing = RIGHT;
                entity.sprite.setTextureRect(sf::IntRect(0, 0, enemyRect.width, enemyRect.height));
                float offSet = (rightWallRect.left+rightWallRect.width)-enemyCollision.x;
                //adjust the enemy to be position next to the wall
                entity.sprite.move(offSet,0);
                enemyRect = entity.sprite.getGlobalBounds();
                enemyCollision =
                        {enemyRect.left+entity.localCollisionPoint.x,
                         enemyRect.top+entity.localCollisionPoint.y};
            }
            if(entity.acceleration->y >0){
                pit++;
                continue;
            }
            //Ceiling detection
            sf::FloatRect ceilingRect = {
                    platformRect.left-entity.localCollisionPoint.x+1,//makes sure you don't hit a ceiling
                    //after being displaced by a wall
                    platformRect.top+platformRect.height,
                    platformRect.width+entity.localCollisionPoint.x,
                    entity.localCollisionPoint.y
            };
            if(ceilingRect.contains(enemyCollision)){
                float offSet = (ceilingRect.top+ceilingRect.height)-enemyCollision.y;
                entity.sprite.move(0,offSet);
                entity.acceleration->y=0;
            }
            pit++;
        }
        if(!platformIntersected){
            entity.grounded = false;
        }

}


void Stage::update(sf::Time elapsedTime,sf::View *view,sf::RenderWindow *window,GameState &gameState){
    player->update(elapsedTime,gameState);

    if(gameState == GameState::Playing){
        checkPlayerCollisions(elapsedTime);
        checkEnemyCollisions(elapsedTime);
        sf::FloatRect playerRect = player->sprite.getGlobalBounds();
        //adjust camera in x
        sf::FloatRect viewport = view->getViewport();

            //adjust camera to the right
        int upperCameraBound = view->getCenter().y-200;
        int lowerCameraBound = view->getCenter().y;
        int leftCameraBound = view->getCenter().x-100;
        int rightCameraBound = leftCameraBound+200;
        if(playerRect.left+playerRect.width > rightCameraBound ){
            int xOffset = playerRect.left+playerRect.width-rightCameraBound;
            view->move(xOffset,0);

        }
            //adjust camera to the left
        if(view->getCenter().x - viewport.width/2 > this->origin.x &&  playerRect.left < leftCameraBound){
            int xOffset = playerRect.left-leftCameraBound;

            view->move(xOffset,0);

        }
        //adjust camera in y
            //adjust camera upwards
        if(playerRect.top <  upperCameraBound){
            int yOffset = playerRect.top-upperCameraBound;
            view->move(0,yOffset);

        }
            //adjust camera downwards
        if(view->getCenter().y + viewport.height/2 < this->origin.y && playerRect.top+playerRect.height > lowerCameraBound){
            int yOffset = (playerRect.top+playerRect.height) - lowerCameraBound;
            view->move(0,yOffset);

        }

        window->setView(*view);

    }
}
void Stage::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(this->background, states);
    target.draw(*this->player);

    //draw platforms
    std::vector<Platform*>::const_iterator pit = this->platforms.begin();
    while(pit != platforms.end()){
        target.draw(**pit);
        pit++;
    }
    //draw enemies
    std::vector<Enemy*>::const_iterator eit = this->enemies.begin();
    while(eit != enemies.end()){
        target.draw(**eit);
        eit++;
    }
    //draw collisions por platforms (only if debug is turned on)
    if(this->debug){
        std::vector<sf::RectangleShape>::const_iterator cit = this->collisions.begin();
        while(cit != collisions.end()){
            target.draw(*cit);
            cit++;
        }
    }


}