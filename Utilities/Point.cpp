//
// Created by Jorge on 6/6/2017.
//

#include "Point.h"

Point::Point(int x = 0, int y =0){
    this->x = x;
    this->y = y;
}
float Point::distance(Point p2){
    return sqrt(pow(p2.x-this->x,2)+pow(p2.y-this->y,2) );
}