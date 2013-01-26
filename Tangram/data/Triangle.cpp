#include "Triangle.h"

Triangle::Triangle(){
    size=3;
    xmin=0;
    xmax=20;
    ymin=0;
    ymax=20;
    points[0]=wxPoint(0,0);
    points[1]=wxPoint(20,0);
    points[2]=wxPoint(20,20);
    start_vectors[0]=Vector(0,0);
    start_vectors[1]=Vector(20,0);
    start_vectors[2]=Vector(20,20);
}

Triangle::Triangle(wxPoint p1,wxPoint p2,wxPoint p3){
    size=3;
    xmin=MinMaxUtils::MinX(p1,p2,p3);
    xmax=MinMaxUtils::MaxX(p1,p2,p3);
    ymin=MinMaxUtils::MinY(p1,p2,p3);
    ymax=MinMaxUtils::MaxY(p1,p2,p3);
    points[0]=p1;
    points[1]=p2;
    points[2]=p3;  
    start_vectors[0]=Vector(p1.x,p1.y);
    start_vectors[1]=Vector(p2.x,p2.y);
    start_vectors[2]=Vector(p3.x,p3.y);
}

void Triangle::Set(wxPoint p1,wxPoint p2,wxPoint p3){
    xmin=MinMaxUtils::MinX(p1,p2,p3);
    xmax=MinMaxUtils::MaxX(p1,p2,p3);
    ymin=MinMaxUtils::MinY(p1,p2,p3);
    ymax=MinMaxUtils::MaxY(p1,p2,p3);
    points[0]=p1;
    points[1]=p2;
    points[2]=p3;
}

void Triangle::Set(wxPoint p1,wxPoint p2,wxPoint p3,wxPoint p4){}
    
void Triangle::SetP1(wxPoint p1){
    points[0]=p1; 
    xmin=MinMaxUtils::MinX(points[0],points[1],points[2]);
    xmax=MinMaxUtils::MaxX(points[0],points[1],points[2]);
    ymin=MinMaxUtils::MinY(points[0],points[1],points[2]);
    ymax=MinMaxUtils::MaxY(points[0],points[1],points[2]);
}
void Triangle::SetP2(wxPoint p2){
    points[1]=p2;
    xmin=MinMaxUtils::MinX(points[0],points[1],points[2]);
    xmax=MinMaxUtils::MaxX(points[0],points[1],points[2]);
    ymin=MinMaxUtils::MinY(points[0],points[1],points[2]);
    ymax=MinMaxUtils::MaxY(points[0],points[1],points[2]);
}
void Triangle::SetP3(wxPoint p3){
    points[2]=p3; 
    xmin=MinMaxUtils::MinX(points[0],points[1],points[2]);
    xmax=MinMaxUtils::MaxX(points[0],points[1],points[2]);
    ymin=MinMaxUtils::MinY(points[0],points[1],points[2]);
    ymax=MinMaxUtils::MaxY(points[0],points[1],points[2]);
}
void Triangle::SetP4(wxPoint p4){}
