#include "Rectangle.h"

Rect::Rect(){
    xmin=0;
    xmax=20;
    ymin=0;
    ymax=20;
    points[0]=wxPoint(0,0);
    points[1]=wxPoint(20,0);
    points[2]=wxPoint(20,20);
    points[3]=wxPoint(0,20);
}

Rect::Rect(wxPoint p1,wxPoint p2,wxPoint p3, wxPoint p4){
    points[0]=p1;
    points[1]=p2;
    points[2]=p3;
    points[3]=p4;   
}
void Rect::Print(void){
    printf("Rect:\n");
    for(int i=0;i<4;i++){
        printf("[%d,%d]\n",points[i].x,points[i].y);
    }
    printf("----------\n");   
}
void Rect::Set(wxPoint p1,wxPoint p2,wxPoint p3, wxPoint p4){
    points[0]=p1;
    points[1]=p2;
    points[2]=p3;
    points[3]=p4;   
}
    
void Rect::SetP1(wxPoint p1){
    points[0]=p1;     
}
void Rect::SetP2(wxPoint p2){
    points[1]=p2;
}
void Rect::SetP3(wxPoint p3){
    points[2]=p3;    
}
void Rect::SetP4(wxPoint p4){
    points[3]=p4;    
}
    
wxPoint Rect::GetP1(){
    return points[0];
}
wxPoint Rect::GetP2(){
    return points[1];
}
wxPoint Rect::GetP3(){
    return points[2];
}
wxPoint Rect::GetP4(){
    return points[3];
}

bool Rect::IsInner(int x,int y){
 return true;   
}
 
wxPoint* Rect::GetPoints(){
    return points;   
}

