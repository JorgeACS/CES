#include <SFML/Graphics.hpp>
#include "Entities/Player.h"
#include "LevelManager/Stage.h"
#include <fstream>
#include "Utilities/MenuStates.h"
#include <SFML/Audio.hpp>
#include "Utilities/Transition.h"
#include "Utilities/Window.h"
void update(sf::Time,Stage *,sf::View *,sf::RenderWindow *,GameState &,sf::RectangleShape &);
void draw(sf::RenderWindow *,sf::View *,Stage *,GameState &,sf::Font *,sf::RectangleShape);
void loadStage(Stage *&,int);
void parseStage(Stage *&,int);

int main() {
    GameState gameState = GameState::Menu;
    MenuState menuState = MenuState::TitleScreen;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Heart",sf::Style::Resize);
    window.setFramerateLimit(60);
    sf::Clock clock;
    sf::View view(sf::FloatRect(0,0,WINDOW_WIDTH,WINDOW_HEIGHT));
    window.setView(view);
    Stage *stage;
    sf::RectangleShape transition;
    transition.setSize({WINDOW_WIDTH,WINDOW_HEIGHT});
    transition.setPosition(0,0);
    transition.setFillColor({0,0,0,0});
    sf::Font font;
    if (!font.loadFromFile("../Fonts/micross.ttf")) {
        // error...
    }

    loadStage(stage,1);
    //stage->toggleDebug();
    sf::SoundBuffer soundBuffer;
    soundBuffer.loadFromFile("../Sound/test1.wav");
    sf::Sound musicita;
    musicita.setBuffer(soundBuffer);
    musicita.setLoop(true);
    //musicita.play();
    //musicita.
    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            window.close();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            musicita.setPitch(musicita.getPitch()+0.001f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            musicita.setPitch(musicita.getPitch()-0.001f);
        }
        update(elapsed,stage,&view,&window,gameState,transition);
        draw(&window,&view,stage,gameState,&font,transition);



    }

    return 0;
}

void loadStage(Stage *&stage,int stageID){
    parseStage(stage,stageID);
    switch(stageID){
        case(1):{
            Player *player = new Player(200,0,5,0,"player");
            stage = new Stage(2400,600,"../Images/Backgrounds/background.png",player,Stage::stretchY);
            stage->setOrigin({0,WINDOW_HEIGHT/2});
            stage->addPlatform(-500,500,2400,100,"platform2",Platform::stretchY,0);
            stage->addPlatform(500,400,320,64,"platform1",Platform::none,0);
            stage->addPlatform(550,200,256,64,"platform1",Platform::none,0);
            stage->addPlatform(1000,0,96,500,"platform1",Platform::none,0);
            stage->addPlatform(200,200,100,50,"platform1",Platform::none,0);

            stage->addPlatform(1300,300,200,200,"platform1",Platform::none,0);
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
void update(sf::Time elapsedTime,Stage *stage,sf::View *view,sf::RenderWindow *window,GameState &gameState,sf::RectangleShape &transition){
    if(gameState == GameState::Playing || gameState == GameState::Paused){
        stage->update(elapsedTime,view,window,gameState);
    }
    if(gameState == GameState::Menu){
        if(transition.getFillColor().a > 0 &&  transition.getFillColor().a < 255){
            transition.setFillColor({0,0,0,sf::Uint8(transition.getFillColor().a+5)});
            if(transition.getFillColor().a == 255){

                gameState = GameState::Playing;
                std::cout<<"hola";
                transition.setFillColor({0,0,0,0});
            }
        }else {

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                transition.setFillColor({0,0,0,5});
            }
        }

    }

}
void draw(sf::RenderWindow *window,sf::View *view,Stage * stage,GameState &gameState,sf::Font *font,sf::RectangleShape transition){

    window->clear();
    if(gameState == GameState::Playing || gameState == GameState::Paused){
        if(stage){
            window->draw(*stage);
        }
    }

    if(gameState == GameState::Paused){

        sf::RectangleShape pauseScreen;
        sf::Vector2f center = view->getCenter();
        pauseScreen.setSize(sf::Vector2f(WINDOW_WIDTH,WINDOW_HEIGHT));
        pauseScreen.setPosition(center.x-WINDOW_WIDTH/2,center.y-WINDOW_HEIGHT/2);
        sf::Color *color = new sf::Color(0,0,0,156);
        pauseScreen.setFillColor(*color);

        window->draw(pauseScreen);

        sf::Text pauseScreenText;
        pauseScreenText.setFont(*font);
        pauseScreenText.setString("Paused!");
        pauseScreenText.setCharacterSize(24);
        pauseScreenText.setFillColor(sf::Color::White);
        pauseScreenText.setOutlineColor(sf::Color::Black);
        pauseScreenText.setPosition(center.x-50,center.y);
        window->draw(pauseScreenText);
    }

    if(gameState == GameState::Menu){
        sf::RectangleShape menuScreen;
        menuScreen.setSize(sf::Vector2f(WINDOW_WIDTH,WINDOW_HEIGHT));
        sf::Color *color = new sf::Color(20,200,200,255);
        menuScreen.setFillColor(*color);



        window->draw(menuScreen);
        sf::Text menuText;
        menuText.setFont(*font);
        menuText.setCharacterSize(24);
        menuText.setFillColor(sf::Color::White);
        menuText.setOutlineColor(sf::Color::Black);
        menuText.setOutlineThickness(3);
        menuText.setPosition(300,250);
        menuText.setString("Press Space to play!");
        window->draw(menuText);

        menuText.setCharacterSize(50);
        menuText.setPosition(WINDOW_WIDTH/2-50,20);
        menuText.setString("Heart");
        window->draw(menuText);
        window->draw(transition);
    }
    window->display();
    return;
}