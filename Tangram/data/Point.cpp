#include "Point.h"

Point::Point(){
    _x=0;
    _y=0;
}
Point::Point(int x,int y){
    _x=x;
    _y=y;
}

void Point::Print(void){
    printf("[d,%d]\n",_x,_y);
}

void Point::Set(int x,int y){
    _x=x;
    _y=y;
}
 void Point::SetX(int x){
    _x=x;
}
 void Point::SetY(int y){
    _y=y;
}
 int Point::GetX(){
    return _x;
}
 int Point::GetY(){
    return _y;
}
