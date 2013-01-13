#include "Tan.h"

bool Tan::IsIn(int x,int y) {
    return ( x>=xmin && x<=xmax && y>=ymin && y<=ymax );
}
bool Tan::IsIn(Tan* tan) {
    //printf("[%d,%d] x [%d,%d]    przeciwko   [%d,%d] x [%d,%d]\n",tan->xmin,tan->xmax,tan->ymin,tan->ymax,xmin,xmax,ymin,ymax);
    return ((tan->xmin <= xmax && tan->xmax >= xmin) && (tan->ymin <= ymax && tan->ymax >= ymin));
}

bool Tan::IsCrossing(Tan* tan) {
    wxPoint* points=GetPoints();
    wxPoint* pointsToCheck=tan->GetPoints();
    for(int i=0;i<GetSize();i++){
        for(int j=0;j<tan->GetSize();j++){
            if(VectorUtils::IsCrossing(points[i],points[(i+1)%GetSize()],pointsToCheck[j],pointsToCheck[(j+1)%tan->GetSize()])) {
                return true;
            }
        }   
    }
    return false;
}

bool Tan::IsInCenterCircle(int x,int y){
    //pobieram œrodek figury
    wxPoint center=GetCenter(); 
    int centerX=center.x; int centerY=center.y;  
    //pobieram normê wektora od srodka figury do punktu klikniêcia     
    double norm=VectorUtils::Norm(wxPoint(x-centerX,y-centerY));
    //jezeli norma jest mniejsza od IN_CIRCLE_FACTOR * norma odleglosci pierwszego wierzcholka od srodka tana - trafiono
    if(norm/VectorUtils::Norm(wxPoint(points[0].x-centerX,points[0].y-centerY))<IN_CIRCLE_FACTOR){
        return true;   
    }
    return false;
}

bool Tan::IsOutsidePanel(){
    wxPoint* points=GetPoints();
    for(int i=0;i<GetSize();i++){
        if(points[i].x < 0 || points[i].x > WIDTH || points[i].y < 0 || points[i].y > HEIGHT) return true;
    }   
    return false;
}

bool Tan::Conflicts(Tan* toCheck,Tan** tans){
    for(int i=0;i<TANS_NO;i++){
        if(tans[i]!=this && tans[i]->IsIn(toCheck)) {
            if(tans[i]->IsCrossing(toCheck)) return true;
        }   
    }
    return false;
}

bool Tan::IsInner(Tan* toCheck, Tan* conflicted){
    wxPoint* pointsToCheck=toCheck->GetPoints();
    wxPoint* pointsConflicted=conflicted->GetPoints();
    for(int i=0;i<toCheck->GetSize();i++){
        if(conflicted->IsInner(pointsToCheck[i].x,pointsToCheck[i].y)) return true;    
    }   
    for(int i=0;i<conflicted->GetSize();i++){
        if(toCheck->IsInner(pointsConflicted[i].x,pointsConflicted[i].y)) return true;    
    }
    return false;
}

void Tan::Print(void){
    for(int i=0;i<GetSize();i++){
        printf("[%d,%d]\n",points[i].x,points[i].y);
    }
    printf("----------\n");   
}

int Tan::GetSize(){
    return size;   
}

wxPoint Tan::GetCenter(){
    wxPoint* points=GetPoints();
    int centerX=0;
    int centerY=0;
    for(int i=0;i<GetSize();i++){
        centerX+=points[i].x;
        centerY+=points[i].y;   
    }
    centerX/=GetSize();
    centerY/=GetSize();
    return wxPoint(centerX,centerY);
}
 
wxPoint* Tan::GetPoints() {
    return points;   
}

wxPoint Tan::GetP1(){
    return points[0];
}
wxPoint Tan::GetP2(){
    return points[1];
}
wxPoint Tan::GetP3(){
    return points[2];
}
wxPoint Tan::GetP4(){
    return points[3];
} 

void Tan::SetP(int i,wxPoint p){
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
