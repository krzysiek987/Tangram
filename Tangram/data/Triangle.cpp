#include "Triangle.h"

Triangle::Triangle(){
    size=3;
    points[0]=wxPoint(0,0);
    points[1]=wxPoint(20,0);
    points[2]=wxPoint(20,20);
}

Triangle::Triangle(wxPoint p1,wxPoint p2,wxPoint p3){
    size=3;
    points[0]=p1;
    points[1]=p2;
    points[2]=p3;  
}
void Triangle::Print(void){
    printf("Triangle:\n");
    for(int i=0;i<3;i++){
        printf("[%d,%d]\n",points[i].x,points[i].y);
    }
    printf("----------\n");   
}
void Triangle::Set(wxPoint p1,wxPoint p2,wxPoint p3){
    points[0]=p1;
    points[1]=p2;
    points[2]=p3;
}
    
void Triangle::SetP1(wxPoint p1){
    points[0]=p1;     
}
void Triangle::SetP2(wxPoint p2){
    points[1]=p2;
}
void Triangle::SetP3(wxPoint p3){
    points[2]=p3;    
}

    
wxPoint Triangle::GetP1(){
    return points[0];
}
wxPoint Triangle::GetP2(){
    return points[1];
}
wxPoint Triangle::GetP3(){
    return points[2];
}
 
wxPoint* Triangle::GetPoints(){
    return points;   
}

