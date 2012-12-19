#include "Rectangle.h"

Rectangle::Rectangle(){
    for(int i=0;i<4;i++){
        points[i]=new Point();
    }
}

Rectangle(Point p1,Point p2,Point p3, Point p4){
    points[0]=p1;
    points[1]=p2;
    points[2]=p3;
    points[3]=p4;   
}
void Print(void){
    printf("Rectangle:\n");
    for(int i=0;i<4;i++){
        points[i].Print();
    }
    printf("----------\n");   
}
void Set(Point p1,,Point p2,Point p3, Point p4){
    points[0]=p1;
    points[1]=p2;
    points[2]=p3;
    points[3]=p4;   
}
    
void SetP1(Point p1){
    points[0]=p1;     
}
void SetP2(Point p2){
    points[1]=p2;
}
void SetP3(Point p3){
    points[2]=p3;    
}
void SetP4(Point p4){
    points[3]=p4;    
}
    
Point GetP1(){
    return points[0];
}
Point GetP2(){
    return points[1];
}
Point GetP3(){
    return points[2];
}
Point GetP4(){
    return points[3];
}
 
Point[4] GetPoints(){
    return points;   
}
