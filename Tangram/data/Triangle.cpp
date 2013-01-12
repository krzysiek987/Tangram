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

void Triangle::SetP(int i,wxPoint p){
    switch(i){
        case 1:
            SetP1(p);
            break; 
        case 2:
            SetP2(p);
            break; 
        case 3:
            SetP3(p);
            break; 
        default:
            break;     
    }
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
    double degrees=0.0;
    wxPoint center=wxPoint(x,y);
    for(int i=0;i<size;i++){
        degrees += VectorUtils::AngleBetweenPoints(points[i],center,points[(i+1)%size]);
    }
    return abs(degrees-360.0) < EPSILON ? true : false;    
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
ActualMoveInfo Triangle::Move(int x,int y, Tan** tans){  
    if(xmin+x < 0 || xmax+x > WIDTH){
        x = xmin+x<0 ? -xmin : WIDTH-xmax;
        //printf(" [%d,%d] x [%d,%d]   comp=%d\n", xmin,xmax,ymin,ymax,xmin+x<0);
        //printf("przesuwam x o %d\n",x);
    }
    if(ymin+y < 0 || ymax+y > HEIGHT){
        y = ymin+y<0 ? -ymin : HEIGHT-ymax;
        //printf("przesuwam y o %d\n",y);
    }
    
    Triangle *triangle=new Triangle(wxPoint(points[0].x+x,points[0].y+y),
                                    wxPoint(points[1].x+x,points[1].y+y),
                                    wxPoint(points[2].x+x,points[2].y+y));
    if(!Conflicts(triangle,tans,this)){                               
        xmin+=x;
        xmax+=x;
        ymin+=y;
        ymax+=y;
        for(int i=0;i<size;i++){
            points[i].x+=x;  
            points[i].y+=y;    
        } 
        return ActualMoveInfo(x,y);
    } else {
        return ActualMoveInfo(0,0);   
    }
}
