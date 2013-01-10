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
    xmin=MinMaxUtils::MinX(p1,p2,p3);
    xmax=MinMaxUtils::MaxX(p1,p2,p3);
    ymin=MinMaxUtils::MinY(p1,p2,p3);
    ymax=MinMaxUtils::MaxY(p1,p2,p3);
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
    xmin=MinMaxUtils::MinX(p1,p2,p3);
    xmax=MinMaxUtils::MaxX(p1,p2,p3);
    ymin=MinMaxUtils::MinY(p1,p2,p3);
    ymax=MinMaxUtils::MaxY(p1,p2,p3);
    points[0]=p1;
    points[1]=p2;
    points[2]=p3;
}
    
void Triangle::SetP1(wxPoint p1){
    xmin=MinMaxUtils::Min(xmin,p1.x);
    xmax=MinMaxUtils::Max(xmax,p1.x);
    ymin=MinMaxUtils::Min(ymin,p1.y);
    ymax=MinMaxUtils::Max(ymax,p1.y);
    points[0]=p1;     
}
void Triangle::SetP2(wxPoint p2){
    xmin=MinMaxUtils::Min(xmin,p2.x);
    xmax=MinMaxUtils::Max(xmax,p2.x);
    ymin=MinMaxUtils::Min(ymin,p2.y);
    ymax=MinMaxUtils::Max(ymax,p2.y);
    points[1]=p2;
}
void Triangle::SetP3(wxPoint p3){
    xmin=MinMaxUtils::Min(xmin,p3.x);
    xmax=MinMaxUtils::Max(xmax,p3.x);
    ymin=MinMaxUtils::Min(ymin,p3.y);
    ymax=MinMaxUtils::Max(ymax,p3.y);
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
    double radians=0.0;
    wxPoint center=wxPoint(x,y);
    for(int i=0;i<size;i++){
        radians += VectorUtils::AngleBetweenPoints(points[i],center,points[(i+1)%size]);
    }
    return abs(radians-360.0) < EPSILON ? true : false;    
}

bool Triangle::MoveX(int x){
    if(xmin+x < 0 || xmax+x > WIDTH){
        return false;   
    }
    else {
        xmin+=x;
        xmax+=x;
        for(int i=0;i<size;i++){
            points[i].x+=x;    
        } 
    }
    return true; 
}
bool Triangle::MoveY(int y){
    if(ymin+y < 0 || ymax+y > HEIGHT){
        return false;   
    }
    else {
        ymin+=y;
        ymax+=y;
        for(int i=0;i<size;i++){
            points[i].y+=y;    
        } 
    }
    return true;   
}
bool Triangle::Move(int x,int y){
    if(xmin+x < 0 || xmax+x > WIDTH){
        return false;   
    }
    if(ymin+y < 0 || ymax+y > HEIGHT){
        return false;   
    }
    xmin+=x;
    xmax+=x;
    ymin+=y;
    ymax+=y;
    for(int i=0;i<size;i++){
        points[i].x+=x;  
        points[i].y+=y;    
    } 
    return true;
}
