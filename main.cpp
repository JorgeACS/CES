#include <SFML/Graphics.hpp>
#include "Entities/Player.h"
#include "LevelManager/Stage.h"
#include <fstream>
#include "Containers/TextureContainer.h"


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
void update(sf::Time,Stage *,sf::View *,sf::RenderWindow *,GameState &);
void draw(sf::RenderWindow *,sf::View *,Stage *,sf::Text *,GameState &);
void loadStage(Stage *&,int);
void parseStage(Stage *&,int);

int main() {
    GameState state = GameState::Playing;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Heart",sf::Style::Resize);
    window.setFramerateLimit(60);
    sf::Clock clock;
    sf::View view(sf::FloatRect(0,0,WINDOW_WIDTH,WINDOW_HEIGHT));
    window.setView(view);
    Stage *stage;
    sf::Font font;
    if (!font.loadFromFile("Fonts/micross.ttf")) {
        // error...
    }
    sf::Text pauseScreenText;
    pauseScreenText.setFont(font);
    pauseScreenText.setString("Paused!");
    pauseScreenText.setCharacterSize(24);
    pauseScreenText.setFillColor(sf::Color::White);
    pauseScreenText.setOutlineColor(sf::Color::Black);
    loadStage(stage,1);
    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        update(elapsed,stage,&view,&window,state);
        draw(&window,&view,stage,&pauseScreenText,state);



    }

    return 0;
}

void loadStage(Stage *&stage,int stageID){
    parseStage(stage,stageID);
    switch(stageID){
        case(1):{

            Player *player = new Player(200,0,5,0,"player");
            stage = new Stage(2400,600,"Images/Backgrounds/background.png",player,Stage::stretchY);
            stage->setOrigin({0,WINDOW_HEIGHT/2});
            stage->addPlatform(-500,500,2400,100,"platform2",Platform::stretchY,0);
            stage->addPlatform(500,400,320,64,"platform1",Platform::none,0);
            stage->addPlatform(550,200,256,64,"platform1",Platform::none,0);
            stage->addPlatform(1000,0,96,500,"platform1",Platform::none,0);
            stage->addPlatform(200,200,100,50,"platform1",Platform::none,0);
            stage->addEnemy(900,0,2,0,"enemy1");
            stage->addPlatform(-2000,664,4000,100,"platform1",Platform::none,0,true);
        }
    }
}

void parseStage(Stage *&stage,int stageID){
    std::fstream stageFile;
    std::string stagePath = "Levels/stage";
    stageFile.open("Levels/stage"+std::to_string(stageID)+".txt");
    std::string aux;
    TextureContainer::addTexture("player","Images/Sprites/heart.png",false);
    TextureContainer::addTexture("enemy1","Images/Sprites/greenBlob.png",false);
    TextureContainer::addTexture("platform1","Images/Sprites/smallBrownBrick.png",true);
    TextureContainer::addTexture("platform2","Images/Sprites/platform.png",true);

    /*
    while(!stageFile.eof()){
        stageFile >> aux;
        std::cout << aux << std::endl;
    }
    */
}
void update(sf::Time elapsedTime,Stage *stage,sf::View *view,sf::RenderWindow *window,GameState &state){
    stage->update(elapsedTime,view,window,state);
}
void draw(sf::RenderWindow *window,sf::View *view,Stage * stage,sf::Text *pauseScreenText,GameState &state){

    window->clear();
    if(stage){
        window->draw(*stage);
    }
    if(state == GameState::Paused){
        sf::RectangleShape pauseScreen;
        sf::Vector2f center = view->getCenter();
        pauseScreen.setSize(sf::Vector2f(WINDOW_WIDTH,WINDOW_HEIGHT));
        pauseScreen.setPosition(center.x-WINDOW_WIDTH/2,center.y-WINDOW_HEIGHT/2);
        sf::Color *color = new sf::Color(0,0,0,156);
        pauseScreen.setFillColor(*color);
        pauseScreenText->setPosition(center.x-50,center.y);
        window->draw(pauseScreen);
        window->draw(*pauseScreenText);
    }
    window->display();
    return;
}