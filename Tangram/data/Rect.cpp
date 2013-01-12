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
}
void Rect::Print(void){
    printf("Rect:\n");
    for(int i=0;i<4;i++){
        printf("[%d,%d]\n",points[i].x,points[i].y);
    }
    printf("----------\n");   
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
void Rect::SetP(int i,wxPoint p){
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
        case 4:
            SetP4(p);
            break; 
        default:
            break;     
    }
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
wxPoint* Rect::GetPoints(){
    return points;   
}
int Rect::GetSize(){
    return size;   
}

bool Rect::IsInner(int x,int y){
    double degrees=0.0;
    wxPoint center=wxPoint(x,y);
    for(int i=0;i<size;i++){
        degrees += VectorUtils::AngleBetweenPoints(points[i],center,points[(i+1)%size]);
    }
    return abs(degrees-360.0) < EPSILON ? true : false;   
}

bool Rect::MoveX(int x){
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
bool Rect::MoveY(int y){
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

ActualMoveInfo Rect::Move(int x,int y, Tan** tans){
if(xmin+x < 0 || xmax+x > WIDTH){
        x = xmin+x<0 ? -xmin : WIDTH-xmax;
        //printf(" [%d,%d] x [%d,%d]   comp=%d\n", xmin,xmax,ymin,ymax,xmin+x<0);
        //printf("przesuwam x o %d\n",x);
    }
    if(ymin+y < 0 || ymax+y > HEIGHT){
        y = ymin+y<0 ? -ymin : HEIGHT-ymax;
        //printf("przesuwam y o %d\n",y);
    }
    Rect *rect=new Rect(wxPoint(points[0].x+x,points[0].y+y),
                            wxPoint(points[1].x+x,points[1].y+y),
                            wxPoint(points[2].x+x,points[2].y+y),
                            wxPoint(points[3].x+x,points[3].y+y));
    if(!Conflicts(rect,tans,this)){
        xmin+=x;
        xmax+=x;
        ymin+=y;
        ymax+=y;
        for(int i=0;i<size;i++){
            points[i].x+=x;  
            points[i].y+=y;    
        } 
        return ActualMoveInfo(x,y);
    }
    return ActualMoveInfo(0,0);
}
