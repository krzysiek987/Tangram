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

bool Triangle::IsInner(int x,int y){
    double degrees=0.0;
    wxPoint center=wxPoint(x,y);
    for(int i=0;i<size;i++){
        degrees += VectorUtils::AngleBetweenPoints(points[i],center,points[(i+1)%size]);
    }
    return abs(degrees-360.0) < EPSILON ? true : false;    
}

ActualMoveInfo Triangle::Move(int x,int y, Tan** tans){  
    //jesli po przesuniêciu obiekt nie mieœci³by siê na ekranie zmniejszam iloœæ o któr¹ przesunê
    if(xmin+x < 0 || xmax+x > WIDTH){
        x = xmin+x<0 ? -xmin : WIDTH-xmax;
    }
    if(ymin+y < 0 || ymax+y > HEIGHT){
        y = ymin+y<0 ? -ymin : HEIGHT-ymax;
    }
    //tworzê testowy przesuniêty tan i jeœli nie koliduje on z innymi tanami to przesuwam docelowy tan
    Triangle *triangle=new Triangle(wxPoint(points[0].x+x,points[0].y+y),
                                    wxPoint(points[1].x+x,points[1].y+y),
                                    wxPoint(points[2].x+x,points[2].y+y));
    if(type==2) triangle->type=4;
    if(!Conflicts(triangle,tans)){                               
        xmin+=x;
        xmax+=x;
        ymin+=y;
        ymax+=y;
        for(int i=0;i<size;i++){
            points[i].x+=x;  
            points[i].y+=y;    
        } 
        //zwracam obiekt z informacj¹ o tym o ile przesun¹³ siê tan
        return ActualMoveInfo(x,y);
    } 
    delete triangle;
    //zwracam obiekt z informacj¹ o tym o ile przesun¹³ siê tan - przesuniecie wynosi 0 bo wystapil konflikt
    return ActualMoveInfo(0,0);   
}
