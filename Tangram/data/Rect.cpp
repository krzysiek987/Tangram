#include "Rect.h"

Rect::Rect(){
    size=4;
    xmin=0;
    xmax=20;
    ymin=0;
    ymax=20;
    points[0]=wxPoint(0,0);
    points[1]=wxPoint(20,0);
    points[2]=wxPoint(20,20);
    points[3]=wxPoint(0,20);
    start_vectors[0]=Vector(0,0);
    start_vectors[1]=Vector(20,0);
    start_vectors[2]=Vector(20,20);
    start_vectors[3]=Vector(0,20);
}

Rect::Rect(wxPoint p1,wxPoint p2,wxPoint p3, wxPoint p4){
    size=4;
    xmin=MinMaxUtils::MinX(p1,p2,p3,p4);
    xmax=MinMaxUtils::MaxX(p1,p2,p3,p4);
    ymin=MinMaxUtils::MinY(p1,p2,p3,p4);
    ymax=MinMaxUtils::MaxY(p1,p2,p3,p4);
    points[0]=p1;
    points[1]=p2;
    points[2]=p3;
    points[3]=p4;   
    start_vectors[0]=Vector(p1.x,p1.y);
    start_vectors[1]=Vector(p2.x,p2.y);
    start_vectors[2]=Vector(p3.x,p3.y);
    start_vectors[3]=Vector(p4.x,p4.y);
}

void Rect::Set(wxPoint p1,wxPoint p2,wxPoint p3, wxPoint p4){
    xmin=MinMaxUtils::MinX(p1,p2,p3,p4);
    xmax=MinMaxUtils::MaxX(p1,p2,p3,p4);
    ymin=MinMaxUtils::MinY(p1,p2,p3,p4);
    ymax=MinMaxUtils::MaxY(p1,p2,p3,p4);
    points[0]=p1;
    points[1]=p2;
    points[2]=p3;
    points[3]=p4;   
}
    
void Rect::SetP1(wxPoint p1){
    points[0]=p1;       
    xmin=MinMaxUtils::MinX(points[0],points[1],points[2],points[3]);
    xmax=MinMaxUtils::MaxX(points[0],points[1],points[2],points[3]);
    ymin=MinMaxUtils::MinY(points[0],points[1],points[2],points[3]);
    ymax=MinMaxUtils::MaxY(points[0],points[1],points[2],points[3]);
}
void Rect::SetP2(wxPoint p2){
    points[1]=p2;
    xmin=MinMaxUtils::MinX(points[0],points[1],points[2],points[3]);
    xmax=MinMaxUtils::MaxX(points[0],points[1],points[2],points[3]);
    ymin=MinMaxUtils::MinY(points[0],points[1],points[2],points[3]);
    ymax=MinMaxUtils::MaxY(points[0],points[1],points[2],points[3]);
}
void Rect::SetP3(wxPoint p3){
    points[2]=p3; 
    xmin=MinMaxUtils::MinX(points[0],points[1],points[2],points[3]);
    xmax=MinMaxUtils::MaxX(points[0],points[1],points[2],points[3]);
    ymin=MinMaxUtils::MinY(points[0],points[1],points[2],points[3]);
    ymax=MinMaxUtils::MaxY(points[0],points[1],points[2],points[3]);
}
void Rect::SetP4(wxPoint p4){
    points[3]=p4; 
    xmin=MinMaxUtils::MinX(points[0],points[1],points[2],points[3]);
    xmax=MinMaxUtils::MaxX(points[0],points[1],points[2],points[3]);
    ymin=MinMaxUtils::MinY(points[0],points[1],points[2],points[3]);
    ymax=MinMaxUtils::MaxY(points[0],points[1],points[2],points[3]);
}
