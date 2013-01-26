#include "Tan.h"

Tan::Tan() {
    matrix.data[0][0] = 1.0;
    matrix.data[1][1] = 1.0;
}

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
    wxPoint center,center2;
    for(int i=0;i<TANS_NO;i++){
        if(tans[i]!=this && tans[i]->IsIn(toCheck)) {
            if(tans[i]->IsCrossing(toCheck)) return true;
            center = toCheck->GetCenter();
            if(tans[i]->IsInner(center.x,center.y)) return true;
            center2 = tans[i]->GetCenter();
            if(toCheck->IsInner(center2.x,center2.y)) return true;  
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

bool Tan::IsInner(int x,int y){
    double degrees=0.0;
    wxPoint center=wxPoint(x,y);
    for(int i=0;i<GetSize();i++){
        degrees += VectorUtils::AngleBetweenPoints(points[i],center,points[(i+1)%size]);
    }
    return abs(degrees-360.0) < EPSILON ? true : false;    
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

wxPoint Tan::AttractionShift(Tan** tans){
    wxPoint temp_shift,shift=wxPoint(0,0);
    double min_norm = DISTANCE_OF_ATTRACTION;
    double norm;
    
    for(int i=0;i<TANS_NO;++i){
        if(tans[i]!=this) {
            wxPoint* tan_points = tans[i]->GetPoints();
            wxPoint* check_points = GetPoints();
            for(int j=0;j<GetSize();++j){
                for(int k=0;k<tans[i]->GetSize();++k){
                    temp_shift = tan_points[k]-check_points[j];
                    norm = VectorUtils::Norm(temp_shift);
                    if(norm < DISTANCE_OF_ATTRACTION && norm<min_norm){
                        min_norm = norm;
                        shift = temp_shift;
                    }                    
                }
            }
        }   
    }
  
    return shift;
}

ActualMoveInfo Tan::Move(int x,int y, Tan** tans){
    int move_x = 0;
    int move_y = 0;

    //jesli po przesuniêciu obiekt nie mieœci³by siê na ekranie zmniejszam iloœæ o któr¹ przesunê    
    if(xmin+x < 0 || xmax+x > WIDTH){
        x = xmin+x<0 ? -xmin : WIDTH-xmax;
    }
    if(ymin+y < 0 || ymax+y > HEIGHT){
        y = ymin+y<0 ? -ymin : HEIGHT-ymax;
    }
    
    wxPoint translate = wxPoint(x,y);
    TranslateTan(translate);         
    
    if(!Conflicts(this,tans)){
        move_x=x;
        move_y=y;  
          
    } else {
        TranslateTan(-translate);
    }
    wxPoint shift = AttractionShift(tans);
    if(VectorUtils::Norm(shift)>0){
        TranslateTan(shift);
        if(!Conflicts(this,tans)){
            move_x=x+shift.x;
            move_y=y+shift.y;
        }
        else {
            TranslateTan(-shift);
        }
        
    }
    //zwracam obiekt z informacj¹ o tym o ile przesun¹³ siê tan
    return ActualMoveInfo(move_x,move_y);
}

/*
 * Metoda obraca tan o podany k¹t wzglêdem podanego punktu
 */
void Tan::RotateTan(double radius,wxPoint rotate_point)
{
    Matrix matrix1,matrix2,matrix3;
    matrix1.data[0][0]=1.0,matrix1.data[0][2]=-rotate_point.x;
    matrix1.data[1][1]=1.0,matrix1.data[1][2]=-rotate_point.y;
    
    matrix = matrix1*matrix;
    
    matrix2.data[0][0]=cos(radius); matrix2.data[0][1]=-sin(radius);     
    matrix2.data[1][0]=sin(radius); matrix2.data[1][1]=cos(radius);
    
    matrix = matrix2*matrix;
    
    matrix3.data[0][0]=1.0,matrix3.data[0][2]=rotate_point.x;
    matrix3.data[1][1]=1.0,matrix3.data[1][2]=rotate_point.y;
    
    matrix = matrix3*matrix;
    
    wxPoint temp_point;
    Vector temp_vectors[4];
    
    for(int j=0;j<GetSize();j++){
        matrix.Print();
        temp_vectors[j] = matrix*start_vectors[j];
        temp_point.x = temp_vectors[j].GetX();
        temp_point.y = temp_vectors[j].GetY();
        SetP(j+1,temp_point);
    }   
}

/*
 * Metoda przesuwa tan o wektor zapisany jako punkt
 */
void Tan::TranslateTan(wxPoint translation)
{ 
    matrix.data[0][2]+=translation.x;
    matrix.data[1][2]+=translation.y;
    
    xmin+=translation.x;
    xmax+=translation.x;
    ymin+=translation.y;
    ymax+=translation.y;
    
    for(int j=0;j<GetSize();j++){
        points[j].x+=translation.x;
        points[j].y+=translation.y;
    }   
}
