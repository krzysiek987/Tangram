#ifndef _VECTOR_UTILS_
#define _VECTOR_UTILS_

#include <wx/gdicmn.h>
#include <cmath>
#include <iostream>

/*
 * Klasa z metodami u¿ytkowymi dotycz¹cymi wektorów - iloczyny skalarne itd...
 */
class VectorUtils{
public:
    //iloczyn skalarny dwoch wektorów
    static int ScalarProduct(wxPoint p1, wxPoint p2){
        return p1.x*p2.x+p1.y*p2.y;
    }
    //norma wektora
    static double Norm(wxPoint p1){
        return sqrt((double)p1.x*(double)p1.x+(double)p1.y*p1.y);
    }
    //k¹t miedzy dwoma wektorami
    static double AngleBetweenVectors(wxPoint p1,wxPoint p2){
        if((p1.x==0 && p1.y==0) || (p2.x==0 && p2.y==0)) return 0.0;
        double cos_angle = (double)ScalarProduct(p1,p2)/(Norm(p1)*Norm(p2));
        if(cos_angle>1.0) return 0.0;
        if(cos_angle<-1.0) return M_PI;
        return acos(cos_angle);
    }
    //kat oparty na trzech punktach p1,p2,p3
    static double AngleBetweenPoints(wxPoint p1,wxPoint p2,wxPoint p3){
        return AngleBetweenVectors(wxPoint(p1.x-p2.x,p1.y-p2.y),wxPoint(p3.x-p2.x,p3.y-p2.y))*180/M_PI;
    }
    //kat oparty na trzech punktach p1,p2,p3 w radianach
    static double AngleBetweenPointsInRadians(wxPoint p1,wxPoint p2,wxPoint p3){
        return AngleBetweenVectors(wxPoint(p1.x-p2.x,p1.y-p2.y),wxPoint(p3.x-p2.x,p3.y-p2.y));
    }
    /*
     * metoda zwraca numer cwiartki ukladu wspolrzednych ktorego srodkiem jest (centerX,centerY) w której znajduje sie punkt (eventX,eventY)
     * juz nieuzywana
     */
    static int GetBlock(int  eventX,int eventY, int centerX, int centerY){
        if(eventX >= centerX && eventY <= centerY) return 1;
        else if(eventX < centerX && eventY <= centerY) return 2;
        else if(eventX < centerX && eventY > centerY) return 3;
        else return 4;
    }
    /*
     * metoda sprawdza kierunek w ktorym wykonywany jest obrót
     */
    static int GetDirection(int eventX, int eventY, int centerX, int centerY, int holdedX, int holdedY){        
        int position=(holdedY - centerY)*(eventX - centerX) - (holdedX - centerX)*(eventY - centerY);
        return position;
    }  
    /*
     * metoda liczy wyznacznik macierzy
            [ a.x  a.y  1 ]
            [ b.x  b.y  1 ]
            [ c.x  c.y  1 ]
     */
    static int CountDet(wxPoint a,wxPoint b, wxPoint c){
         return a.x*b.y + b.x*c.y + c.x*a.y - c.x*b.y - a.x*c.y - b.x*a.y;
    }
    /*
     * metoda sprawdza czy odcinki [a,b]  i  [c,d] przecinaj¹ siê
     */
    static bool IsCrossing(wxPoint a,wxPoint b, wxPoint c, wxPoint d){ 
        int d1=CountDet(a,b,c), d2=CountDet(a,b,d);
        int d3=CountDet(c,d,a), d4=CountDet(c,d,b);
        
        return abs(Sign(d1) - Sign(d2)) + abs(Sign(d3) - Sign(d4))==4;
    }

    //nazwyczajniejsze signum z tolerancj¹ (-80,80) dla wartoœci 0 
    //(pozwala to niezauwa¿anie nachodziæ na siebie tanom - wymagane, aby dobrze dzia³a³o przyci¹ganie)
    static int Sign(int x){
        if(abs(x)<80) return 0;
        if(x>0) return 1; 
        return -1;   
    } 
};

#endif
