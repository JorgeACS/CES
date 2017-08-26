//
// Created by Jorge on 8/23/2017.
//

#ifndef UNTITLED_TRANSITION_H
#define UNTITLED_TRANSITION_H
#include "../Utilities/GameStates.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Utilities/Window.h"

namespace Transition{
    static bool transitioning;
    //static GameState oldState;
    static GameState newState;
    static GameState *originalState;
    static sf::Time duration;
    enum TransitionType{
        fadeOut = 1,
        fadeIn = 2,
    };
    static TransitionType transitionType;
    static sf::RectangleShape transitionRect;

    void beginTransition(GameState *oriS,GameState nS,sf::Time d,TransitionType tT){
        //oldState = *oriS;
        newState = nS;
        originalState = oriS;

        duration = d;
        transitionType = tT;
        transitioning = true;
        switch(transitionType){
            case(fadeOut):{
                //transitionRect.setSize({WINDOW_HEIGHT,WINDOW_WIDTH});
                transitionRect.setSize({800,600});
                transitionRect.setPosition(0,0);
                transitionRect.setFillColor({0,0,0,0});
            }
        }
    }
    void update(){
        if(not transitioning) return;
        sf::Color transitionColor = transitionRect.getFillColor();
        if(transitionColor.a < 255){
            transitionRect.setFillColor({0,0,0,transitionColor.a+1});
        }else{
            *originalState = newState;
            transitioning = false;
            return;
        }
    }
    /*
    void (){
        TransitionType aux =
    }*/
    bool inTransition(){return transitioning;};

}
#endif //UNTITLED_TRANSITION_H
