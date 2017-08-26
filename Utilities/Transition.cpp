//
// Created by Jorge on 8/23/2017.
//
/*
#include "Transition.h"

bool Transition::transitioning = true;

void Transition::beginTransition(GameState &oS,GameState nS,sf::Time d,TransitionType tT){
    oldState = oS;
    newState = nS;
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
void Transition::update(){
    sf::Color transitionColor = transitionRect.getFillColor();
    if(transitionColor.a < 255){
        transitionRect.setFillColor({0,0,0,transitionColor.a+1});
    }else{

    }
}
 */

int x;