#include "Triangle.h"

Triangle::Triangle(){
    xmin=0;
    xmax=20;
    ymin=0;
    ymax=20;
    points[0]=wxPoint(0,0);
    points[1]=wxPoint(20,0);
    points[2]=wxPoint(20,20);
}

Triangle::Triangle(wxPoint p1,wxPoint p2,wxPoint p3){
    xmin=PointUtils::MinX(p1,p2,p3);
    xmax=PointUtils::MaxX(p1,p2,p3);
    ymin=PointUtils::MinY(p1,p2,p3);
    ymax=PointUtils::MaxY(p1,p2,p3);
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
    xmin=PointUtils::MinX(p1,p2,p3);
    xmax=PointUtils::MaxX(p1,p2,p3);
    ymin=PointUtils::MinY(p1,p2,p3);
    ymax=PointUtils::MaxY(p1,p2,p3);
    points[0]=p1;
    points[1]=p2;
    points[2]=p3;
}
    
void Triangle::SetP1(wxPoint p1){
    xmin=PointUtils::Min(xmin,p1.x);
    xmax=PointUtils::Max(xmax,p1.x);
    ymin=PointUtils::Min(ymin,p1.y);
    ymax=PointUtils::Max(ymax,p1.y);
    points[0]=p1;     
}
void Triangle::SetP2(wxPoint p2){
    xmin=PointUtils::Min(xmin,p2.x);
    xmax=PointUtils::Max(xmax,p2.x);
    ymin=PointUtils::Min(ymin,p2.y);
    ymax=PointUtils::Max(ymax,p2.y);
    points[1]=p2;
}
void Triangle::SetP3(wxPoint p3){
    xmin=PointUtils::Min(xmin,p3.x);
    xmax=PointUtils::Max(xmax,p3.x);
    ymin=PointUtils::Min(ymin,p3.y);
    ymax=PointUtils::Max(ymax,p3.y);
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
int Triangle::GetSize(){
    return size;   
}

bool Triangle::IsInner(int x,int y){
 return true;   
}

